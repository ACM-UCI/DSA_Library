from math import floor, log2

'''
Dont ask me how this works, it just works
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

