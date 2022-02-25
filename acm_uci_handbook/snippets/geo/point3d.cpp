template <typename T> struct point3d {
    T x,y,z;
    point3d(T x=T{}, T y=T{}, T z=T{}) : x{x}, y{y}, z{z} { }
};
