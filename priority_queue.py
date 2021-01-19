# Priority Queue class for object oriented simps
#   handles comparison a bit more succinctly

from heapq import heappush, heappop, heapify

class PriorityQueue:
    
    '''
    vals - iterable to be added to the heap
    key - a function which maps each element in the heap to how it should be sorted
    '''
    def __init__(self, vals=[], key=None):
        self.key = (lambda x: x) if key == None else key
        self.heap = [(self.key(v), v) for v in vals]
        heapify(self.heap)

    def push(self, v):
        heappush(self.heap, (self.key(v), v))

    def pop(self):
        return heappop(self.heap)[1]

    def peek(self):
        assert len(self.heap) > 0, 'cannot peek empty PriorityQueue'
        return self.heap[0][1]

