from functools reduce

class Vector:
    def __init__(self, dimension, vals=None):
        self.dim = dimension
        if vals == None:
            self.v = [0 for _ in range(dimension)]
        else
            assert len(vals) == self.dim, 'length of vals does not equal the dimension given'
            self.v = list(vals)

    def __len__(self):
        return self.dim

    def __add__(self, other):
        if type(other) == Vector && self.dim == other.dim:
            return Vector(self.dim, [a+b for a,b in zip(self.vals, other.vals)])
        else:
            raise TypeError(f'other must be of type Vector, was of type{type(other)}')

    # only for scaling, do not use for dot product or cross product
    def __mul__(self, other):
        return Vector(self.dim, [a*other for a in self.vals])

    @staticmethod
    def dot_product(a, b):
        assert type(a) == Vector and type(b) == Vector, 'args must be type Vector'
        assert a.dim == b.dim, 'vectors are not of equal length'
        return reduce((lambda x,y: x+y), (x*y for x,y in zip(a,b)))
            

class Matrix:
    def __init__(self, base, height):
        self.N = height
        self.M = base

        self.matrix = [[0 for _ in range(base)] for __ in range(height)]

    def __mul__(self, other):
        assert(type(other) == Matrix)
        assert(self.N == other.M), f'{self}.height != {other}.base'
        assert(self.M == other.N), f'{self}.base != {other}.height'

        product = Matrix(self.N, other.M)
        
        for i in range(other.M):
            for j in range(self.N):
                for k in range(self.M):
                    product.matrix[j][i] += self.matrix[j][k] * other.matrix[k][i]

        return product

    def _pow_helper(self, k):
        if k == 0:
            return Matrix.get_identity(self.N)
        elif k == 1:
            return self
        else:
            m = self._pow_helper(k//2)
            if k%2:
                return m*m*Matrix.get_identity(self.N)
            else:
                return m*m

    def __add__(self, other):
        assert(type(other) == Matrix)
        assert(self.N == other.N)
        assert(self.M == other.M)

        m = Matrix(self.N, self.M)
        for i in range(self.N):
            for j in range(self.M):
                m.matrix[i][j] = self.matrix[i][j] + other.matrix[i][j]

        return m

    def __sub__(self, other):
        pass


    def __pow__(self, k):
        assert(type(k) == int)
        assert(self.N == self.M)
        return self._pow_helper(k)
        
    def __repr(self):
        return f'Matrix({self.M},{self.N})'

    def __str__(self):
        return 'Matrix:\n' + '\n'.join(str(row) for row in self.matrix)
    
    def get_transpose(self):
        assert(self.N == self.M)
        t = Matrix(self.N, self.N)
        for i in range(self.N):
            for j in range(self.N):
                t.matrix[i][j] = self.matrix[j][i]

        return t


    @classmethod
    def get_identity(cls, base):
        identity = Matrix(base, base)
        for i in range(base):
            identity.matrix[i][i] = 1
        return identity


m1 = Matrix(2,3)
m2 = Matrix(3,2)

m1.matrix = [
    [1,2],
    [0,3],
    [2,1],
]

m2.matrix = [
    [2,1,1],
    [1,3,0],
]

print(m1*m2)

m3 = Matrix(2,2)
m3.matrix = [
    [1, 1],
    [1, 0],
]

print(m3**10)

m4 = Matrix(2,2)
m4.matrix = [
    [1, 2],
    [4, 3],
]
print(m4.get_transpose())

print(m3 + m4)

