def arithmetic_sum(start: int, end: int, step: int=1):
    n = 1+(end-start-1)//step;
    if n%2:
        return (start + ((n-1)>>1)*step)*n
    else:
        return (2*start + (n-1)*step)*(n>>1)
