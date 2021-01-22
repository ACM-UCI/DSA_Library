from math import floor, log2

'''
Dont ask me how this works, it just works
You can use this sparse table compute LCP(i,j) for any suffixes i,j by calling SparseTable.query(i,j)
'''
class SparseTable:

    def __init__(self, arr):
        self.A = list(arr)
        self.n = len(self.A)

        log2N = 1
        while (1<<log2N) < len(arr):
            log2N += 1

        self.sparse_table = [ [0 for _ in range(log2N)] for _ in range(len(arr))]
        for i in range(self.n):
            self.sparse_table[i][0] = i
        

        j = 1
        while (1<<j) < self.n:
            i = 0
            while i + (1<<j) - 1 < self.n:
                if self.A[self.sparse_table[i][j-1]] < self.A[self.sparse_table[i + (1<<(j-1))][j-1]]:
                    self.sparse_table[i][j] = self.sparse_table[i][j-1]
                else:
                    self.sparse_table[i][j] = self.sparse_table[i + (1<<(j-1))][j-1]

                i+=1
            j += 1

    def query(self,l, r):
        k = int(floor(log2(r-l+1)))
        if self.A[self.sparse_table[l][k]] <= self.A[self.sparse_table[r-(1<<k)+1][k]]:
            return self.sparse_table[l][k]
        else:
            return self.sparse_table[r-(1<<k)+1][k]


class SuffixArray:

    def __init__(self, s : str):
        self.s = s
        self.n = len(self.s)
        self.SA = [ i for i in range(self.n) ]
        self.RA = [ ord(c) for c in self.s ]
        self._buildSA()

    # ##### Build Suffix Array
    def _buildSA(self):
        i = 0
        while (1<<i) <= self.n:
            self._countSort(1<<i)
            self._countSort(0)

            self._rank(1<<i)

            if self.RA[self.SA[self.n-1]] == self.n-1:
                break
            i += 1

    def _countSort(self, k):
        maxi = max(300, self.n)
        buckets = [0 for _ in range(maxi)]
        for i in range(self.n):
            buckets[self.RA[ (self.SA[i]+k)%self.n ]] += 1

        acc = 0
        for i in range(maxi):
            tmp = buckets[i]
            buckets[i] = acc
            acc += tmp

        tSA = list(self.SA)
        for i in range(self.n):
            newRank = buckets[self.RA[ (tSA[i]+k)%self.n ] ]
            buckets[self.RA[ (tSA[i]+k)%self.n ] ] += 1
            self.SA[newRank] = tSA[i]

    def _rank(self, k):
        tRA = list(self.RA)
        r = 0
        self.RA[self.SA[0]] = 0
        for i in range(1, self.n):
            if tRA[self.SA[i]] != tRA[self.SA[i-1]] or tRA[(self.SA[i]+k)%self.n] != tRA[(self.SA[i-1]+k)%self.n]:
                r += 1
            self.RA[self.SA[i]] = r
    
    # ##### End Build Suffix Array



    # ##### Build Longest Common Prefix Array
    def _buildLCP(self):
        self.LCP = [0 for _ in range(self.n-1)]
        currMatch = 0
        for suffix in range(self.n-1):
            suffixAbove = self.SA[self.RA[suffix] - 1]

            while max(suffix, suffixAbove) + currMatch < self.n and self.s[suffix+currMatch] == self.s[suffixAbove+currMatch]:
                currMatch += 1

            self.LCP[self.RA[suffixAbove]] = currMatch
            currMatch = max(0, currMatch-1)


    # ##### End Longest Common Prefix Array

    def getSuffixArray(self):
        return self.SA

    def getRankArray(self):
        return self.RA

    def getLongestCommonPrefixArray(self):
        self._buildLCP()
        return self.LCP

