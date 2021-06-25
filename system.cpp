// For solving Systems of Linear Equations using Gaussian Elimination (Row Reduction to Row Echelon Form)
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>

template <typename T, typename Equal = std::equal_to<T>>
class System {
    private:
    using Row = std::vector<T>;
    using Matrix = std::vector<Row>;
    int n,m;
    Matrix mat;

    void scaleRow(int row, T scale) { for (T &v : mat[row]) { v*=scale; } }
    void addToRow(int srcRow, int dstRow, T scale=static_cast<T>(1)) { for (int i = 0; i <= m; ++i) { mat[dstRow][i] += mat[srcRow][i]*scale; } }

public:
    System() = delete;
    System(int num_equations, int num_variables) : n{num_equations}, m{num_variables}, mat{Matrix(n, Row(m+1, 0))} { }

    template <typename ForwardIt>
    void fillRow(int row, ForwardIt first, ForwardIt last) { std::copy(first, last, std::begin(mat[row])); }
    void reduce() {
        for (int r = 0; r+1 < n; ++r) {
            std::sort(std::begin(mat) + r, std::end(mat), [](const Row &a, const Row &b)->bool {
                auto itA = std::begin(a);
                auto itB = std::begin(b);
                for (; itA != std::end(a) && itB != std::end(b); ++itA, ++itB) {
                    if (Equal()(*itA, static_cast<T>(0))) {
                        return false;
                    } else if (Equal()(*itB, static_cast<T>(0))) {
                        return true;
                    }
                }
                return true;
            });

            if (Equal()(mat[r][r], static_cast<T>(0))) {
                continue;
            }

            scaleRow(r, static_cast<T>(1)/mat[r][r]);
            for (int rx = r+1; rx < n; ++rx) {
                addToRow(r, rx, -mat[rx][r]);
            }
        }
        scaleRow(n-1, static_cast<T>(1)/mat[n-1][n-1]);

        for (int r = n-1; r > 0; --r) {
            for (int rx = r-1; rx >= 0; --rx) {
                addToRow(r, rx, -mat[rx][r]);
            }
        }
    }

    // Must first reduce system before calling this
    bool isConsistent() {
        for (const Row &row : mat) {
            bool bad = true;
            for (int c = 0; c < m; ++c) if (!Equal()(row[c], static_cast<T>(0))) {
                bad = false;
            }
            if (bad && !Equal()(row[m], static_cast<T>(0))) {
                return false;
            }
        }
        return true;
    }

    // indexes the augmenteded matrix by (row, column)
    T &operator()(int r, int c) { return mat[r][c]; }
    const T &operator()(int r, int c) const { return mat[r][c]; }

    friend std::ostream &operator<<(std::ostream &os, const System<T,Equal> &s) {
        for (const Row &row : s.mat) { for (int i = 0; i < s.m; ++i) { os << row[i] << ' '; } os << " | " << row[s.m] << '\n'; }
        return os;
    }
};

struct Comp {
    bool operator()(const double &a, const double &b) const {
        return std::abs(a-b) <= 1e-7;
    }
};
