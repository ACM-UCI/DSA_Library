/*
 *                                  _        _     _      
 *  ___ _ __   __ _ _ __ ___  ___  | |_ __ _| |__ | | ___ 
 * / __| '_ \ / _` | '__/ __|/ _ \ | __/ _` | '_ \| |/ _ \
 * \__ \ |_) | (_| | |  \__ \  __/ | || (_| | |_) | |  __/
 * |___/ .__/ \__,_|_|  |___/\___|  \__\__,_|_.__/|_|\___|
 *     |_|                                                
 *
 */

/**
 * Spare Tables are static range based query structures which
 * perform range queries in O(1) assuming the applied operation
 * is idempotent [1].
 *
 * The template parameters are as follows:
 *  T - type of individual element in range (must be default
 *      constructible)
 *  IdempotentFunc - A type constructible with default
 *                   initializer and has a functor accepting two
 *                   arguments of type T and returning a value
 *                   of type T
 *
 * [1] (https://mathworld.wolfram.com/Idempotent.html).
 */

#include <vector>

template <typename T, typename IdempotentFunc>
class SparseTable {
private:
    using F = IdempotentFunc;

    int N,K;
    std::vector<std::vector<T>> st;
    std::vector<int> log;

public:
    SparseTable(const std::vector<T> &arr) : N{static_cast<int>(arr.size())}, K{0} {
        while ((1<<K) < N) { ++K; }

        // initialize sparse table
        st.assign(N, std::vector<T>(K+1));
        for (int i = 0; i < N; ++i) { st[i][0] = arr[i]; }

        // fill sparse table
        for (int j = 1; j <= K; ++j)
            for (int i = 0; i + (1<<j) <= N; ++i)
                st[i][j] = F{}(st[i][j-1], st[i+(1<<(j-1))][j-1]);

        // Initialize log mappings
        log.assign(N+1, 0);
        for (int i = 2; i <= N; ++i) log[i] = log[i/2] + 1;
    }

    // Applies IdempotentFunc on all elements in range [l,r)
    // where l is inclusive and r is exclusive
    T query(int l, int r) {
        int j = log[r-l];
        return F{}(st[l][j], st[r-(1<<j)][j]);
    }
};
