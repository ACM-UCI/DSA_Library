
## BEGIN SEG TREE CLASS ==========
class SegTree:

    def __init__(self, numElements: int, defaultValue, associativeFunct):
        self.size = 1
        self.default = defaultValue
        self.funct = associativeFunct

        while self.size < numElements:
            self.size = (self.size<<1)

        self.st = [self.default for _ in range(self.size<<1)]

    ## CLASS FUNCTIONALITY ##########
    @staticmethod
    def _left(x):
        return (x<<1) + 1

    @staticmethod
    def _right(x): 
        return (x<<1) + 2

    @staticmethod
    def _mid(l, r):
        return (r-l)//2 + l

    ## END CLASS FUNCTIONALITY ##########


    ## PRIVATE FUNCTIONALITY ##########
    def _build(self, elements, x, lx, rx):
        if rx-lx == 1:
            if lx < len(elements):
                self.st[x] = elements[lx]
            return
        mx = SegTree._mid(lx,rx)
        self._build(elements, SegTree._left(x), lx, mx)
        self._build(elements, SegTree._right(x), mx, rx)
        self.st[x] = self.funct(self.st[SegTree._left(x)], self.st[SegTree._right(x)])

    def _set(self, i, v, x, lx, rx):
        if rx-lx == 1:
            self.st[x] = v
            return
        mx = SegTree._mid(lx,rx)
        if i < mx:
            self._set(i, v, SegTree._left(x), lx, mx)
        else:
            self._set(i, v, SegTree._right(x), mx, rx)

        self.st[x] = self.funct(self.st[SegTree._left(x)], self.st[SegTree._right(x)])

    def _range_query(self, l, r, x, lx, rx):
        if rx <= l or r <= lx:
            return self.default
        elif l <= lx and rx <= r:
            return self.st[x]
        else:
            mx = SegTree._mid(lx,rx)
            res1 = self._range_query(l,r,SegTree._left(x),lx,mx)
            res2 = self._range_query(l,r,SegTree._right(x),mx,rx)
            return self.funct(res1, res2)

    def _print_debug_elements(self, x, lx, rx):
        if rx-lx == 1:
            return ','.join(str(self.st[x+i]) for i in range(0,self.size))
        else:
            return self._print_debug_elements(SegTree._left(x), lx, SegTree._mid(lx,rx))

    ## END PRIVATE FUNCTIONALITY ##########


    ## INTERFACE FUNCTIONALITY ##########

    def build(self, elements: list):
        self._build(elements, 0, 0, self.size)

    def set(self, i, v):
        self._set(i, v, 0, 0, self.size)

    def range_query(self, l, r):
        return self._range_query(l, r, 0, 0, self.size)

    def __repr__(self):
        header = f'SegTree: (size={self.size}, default={self.default})'
        data = self._print_debug_elements(0, 0, self.size)
        return header + '\n' + data + '\n'

    ## END INTERFACE FUNCTIONALITY ##########

## END SEG TREE CLASS ##########

