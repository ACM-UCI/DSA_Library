double geometric_sum(int start, int end, double a) {
    return (std::pow(a,start) - std::pow(a,end))/(1.0-a);
}
