#include <ostream>
#include <algorithm>
#include <vector>
#include <numeric>

template <typename T=char, T term='$'>
class SuffixArray {
public:
    class LCP;

private:
    size_t size;
    std::vector<T> str;
    std::vector<int> sa;
    std::vector<int> ra;

public:
    template <typename InputIt>
    SuffixArray(InputIt first, InputIt last) : size{0} {
        for (InputIt cur = first; cur != last; ++cur, ++size);
        ++size; // determine size
        str.assign(size, T{}); sa.assign(size, 0); ra.assign(size, 0);
        std::copy(first, last, std::begin(str)); str[size-1] = term;
        std::iota(std::begin(sa), std::end(sa), 0);
        std::transform(std::begin(str), std::end(str), std::begin(ra),
                [](const T &v) ->int { return static_cast<int>(v); });

        std::stable_sort(std::begin(sa), std::end(sa),
                [&](const int &a, const int &b)->bool {
                    return ra[a] < ra[b];
                });
        rerank(0); // allows the handling of negative values
        for (int k = 0; (1<<k) <= static_cast<int>(size); ++k) {
            for (int i = 0; i < static_cast<int>(size); ++i) {
                sa[i] = (sa[i] - (1<<k) + ((int) size)) % ((int) size);
            }
            countSort();
            rerank(1<<k);

            if (ra[sa[size-1]] == static_cast<int>(size)-1) break;
        }
    }

private:
    void countSort() {
        std::vector<int> cnt(size, 0);
        for (const int rank : ra) { ++cnt[rank]; }
        int sum = 0; for (int &c : cnt) { int tmp = c; c = sum; sum += tmp; }

        std::vector<int> sa_(size, 0);
        for (const int cur : sa) { sa_[cnt[ra[cur]]++] = cur; }
        sa = sa_;
    }

    void rerank(int k) {
        std::vector<int> ra_(size, 0);
        int r = ra_[sa[0]] = 0;
        for (int i = 1; i < static_cast<int>(size); ++i) {
            int newL=ra[sa[i]],     newR=ra[(sa[i]+k)%size];
            int preL=ra[sa[i-1]],   preR=ra[(sa[i-1]+k)%size];
            if (newL != preL || newR != preR) ++r;
            ra_[sa[i]] = r;
        }
        ra = ra_;
    }

public:
    size_t getSize() const { return size; }
    int getRank(int suffix) const { return ra[suffix]; }
    int operator[] (const int &i) const { return sa[i]; }

    SuffixArray<T,term>::LCP getLCP() const {
        return SuffixArray<T,term>::LCP(*this);
    }

    class LCP {
    private:
        size_t size;
        std::vector<int> lcp;
    public:
        LCP(const SuffixArray &suf_arr)
        : size{std::max(size_t{},suf_arr.getSize())},
                lcp{std::vector<int>(size, 0)} {
            int curMatch = 0;
            for (int i = 0; i < static_cast<int>(suf_arr.getSize())-1; ++i) {
                int curSuffixRank = suf_arr.getRank(i);
                if (curSuffixRank == 0) {
                    curMatch = lcp[curSuffixRank] = 0; continue;
                }
                int suffixAbove = suf_arr[curSuffixRank - 1];

                while (suf_arr.str[i+curMatch] ==
                        suf_arr.str[suffixAbove+curMatch])
                    ++curMatch;

                lcp[curSuffixRank] = curMatch;
                curMatch = std::max(0, curMatch-1);
            }
        }

        size_t getSize() const { return size; }
        int operator[](const int &i) const { return lcp[i]; }
    };

};
