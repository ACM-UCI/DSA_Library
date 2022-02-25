template <typename T> struct line2d {
    T a,b,c; // ax + by + c = 0
    line2d(T a, T b, T c) : a{a}, b{b}, c{c} { }

    // This constructor only works for T=double
    line2d(const geo::point2d<T> &a, const geo::point2d<T> &b) {
        if (std::abs(a.x - b.x) < 0.000001) { // be careful with floating points
            // This is a vertical line
            this->a = T{1}; this->b = T{0}; this->c = T{-a.x};
        } else {
            this->a = - (a.y - b.y) / (a.x - b.x);
            this->b = T{1};
            this->c = - (this->a * a.x) - a.y;
        }
    }
};
