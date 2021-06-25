#include <iostream>
#include <istream>
#include <ostream>

template <typename T=long long>
class Fraction {
private:
    static T gcd(T a, T b) {
        return b == static_cast<T>(0) ? a : gcd(b, a%b);
    }
private:
    T n,d;

    void simplify() {
        if (d == static_cast<T>(0)) { n = (n >= 0 ? static_cast<T>(1) : static_cast<T>(-1)); return; }
        if (n == static_cast<T>(0)) { d = static_cast<T>(1); return; }

        T signNum = n/std::abs(n);
        T signDen = d/std::abs(d);
        T sign = signNum * signDen;

        n = std::abs(n); d = std::abs(d);
        T g = gcd(n, d);
        n /= g; d /= g;
        n *= sign;
    }

public:
    Fraction() : n{static_cast<T>(0)}, d{static_cast<T>(1)} { }
    Fraction(T v) : n{v}, d{static_cast<T>(1)} { }
    Fraction(T numerator, T denominator) : n{numerator}, d{denominator} { simplify(); }
    Fraction(const Fraction<T> &copy) : n{copy.n}, d{copy.d} { }

    Fraction<T> &operator=(const Fraction<T> &ass) { n = ass.n; d = ass.d; return *this; }


    bool isPos() const { return (n > 0 && d > 0) || (n < 0 && d < 0) || (n > 0 && d == 0); }
    bool isNeg() const { return (n > 0 && d < 0) || (n < 0 && d > 0) || (n < 0 && d == 0); }
    bool isInf() const { return d == 0; }
    Fraction<T> reciprocol() const { return Fraction(d,n); }
    Fraction<T> pow(int k) const {
        if (k == 0) { return Fraction<T>(1); }
        else if (k == 1) { return Fraction<T>(*this); }
        else if (k < 0) { return pow(-k).reciprocol(); }
        else { Fraction<T> res = pow(k/2); return (k&1) ? res*res*(*this) : res*res; }
    }
    T remainder() const { T res = n%d; return res >= 0 ? res : res + d; }
    T round() const { T rem = remainder(); return (rem >= d - rem) ? (isNeg() ? n/d : (n+d)/d) : (isNeg() ? (n-d+static_cast<T>(1))/d : n/d); }
    
    Fraction<T> operator+   (const Fraction<T> &other) const    { return Fraction(n*other.d + d*other.n, d*other.d); }
    Fraction<T> &operator+= (const Fraction<T> &other)          { n = n*other.d + d*other.n; d *= other.d; simplify(); return *this; }
    Fraction<T> operator-   (const Fraction<T> &other) const    { return Fraction(n*other.d - d*other.n, d*other.d); }
    Fraction<T> &operator-= (const Fraction<T> &other)          { n = n*other.d - d*other.n; d *= other.d; simplify(); return *this; }
    Fraction<T> operator*   (const Fraction<T> &other) const    { return Fraction(n*other.n, d*other.d); }
    Fraction<T> &operator*= (const Fraction<T> &other)          { n = n*other.n; d = d*other.d; simplify(); return *this; }

    Fraction<T> operator/   (const Fraction<T> &other) const    { return Fraction(n*other.d, d*other.n); }
    Fraction<T> &operator/= (const Fraction<T> &other)          { n = n*other.d; d = d*other.n; simplify(); return *this; }

    Fraction<T> operator-   ()                         const    { return Fraction(-n, d); }
    bool        operator==  (const Fraction<T> &other) const    { return n == other.n && d == other.d; }
    bool        operator!=  (const Fraction<T> &other) const    { return n != other.n || d != other.d; }
    bool        operator<   (const Fraction<T> &other) const    { return n*other.d < other.n*d; }
    bool        operator<=  (const Fraction<T> &other) const    { return n*other.d <= other.n*d; }
    bool        operator>   (const Fraction<T> &other) const    { return n*other.d > other.n*d; }
    bool        operator>=  (const Fraction<T> &other) const    { return n*other.d >= other.n*d; }
    operator double() { return static_cast<double>(n)/static_cast<double>(d); }

    friend std::istream &operator>>(std::istream &os, Fraction<T> &f) { T v; os >> v; f.n = v; f.d = 1; return os; }

    friend std::ostream &operator<<(std::ostream &os, const Fraction<T> &f) {
        if (f.d == static_cast<T>(0)) { if (f.isNeg()) { os << "-inf"; } else { os << "inf"; } }
        else if (f.d == static_cast<T>(1)) { os << f.n; }
        else { os << f.n << '/' << f.d; }

        return os;
    }
};

int main() {

    std::cout << "Testing zero ==========================" << std::endl;
    Fraction<int> zero1;
    Fraction<int> zero2(0);
    Fraction<int> zero3(0,1);
    Fraction<int> zero4(0,100);
    Fraction<int> zero5(0,-100);
    std::cout << zero1 << ' ' << zero2 << ' ' << zero3 << ' ' << zero4 << ' ' << zero5 << std::endl;
    std::cout << "Should be: 0 0 0 0 0\n" << std::endl;

    std::cout << "Testing negative ======================" << std::endl;
    Fraction<int> neg1(-1);
    Fraction<int> neg2(-1,2);
    Fraction<int> neg3(1,-3);
    std::cout << neg1 << ' ' << neg2 << ' ' << neg3 << std::endl;
    std::cout << "Should be: -1 -1/2 -1/3\n" << std::endl;

    std::cout << "Testing infinity ======================" << std::endl;
    Fraction<int> inf1(1, 0);
    Fraction<int> inf2(0, 0);
    Fraction<int> inf3(-1, 0);
    std::cout << inf1 << ' ' << inf2 << ' ' << inf3 << std::endl;
    std::cout << "Should be: inf inf -inf\n" << std::endl;

    std::cout << "Testing template ======================" << std::endl;
    Fraction<short> f_short(1,2);
    Fraction<int> f_int(1,3);
    Fraction<long> f_long(1,4);
    Fraction<long long> f_longlong(1,5);
    Fraction f_def(1,6);
    std::cout << f_short << ' ' << f_int << ' ' << f_long << ' ' << f_longlong << ' ' << f_def << std::endl;
    std::cout << "Should be: 1/2 1/3 1/4 1/5 1/6\n" << std::endl;

    std::cout << "Testing simplification ================" << std::endl;
    Fraction<int> simplify1(2,2);
    Fraction<int> simplify2(-2,2);
    Fraction<int> simplify3(14,28);
    Fraction<int> simplify4(28,14);
    Fraction<int> simplify5(29,53);
    std::cout << simplify1 << ' ' << simplify2 << ' ' << simplify3 << ' ' << simplify4 << ' '<< simplify5 << std::endl;
    std::cout << "Should be: 1 -1 1/2 2 29/53\n" << std::endl;

    std::cout << "Testing isPos =========================" << std::endl;
    std::cout << neg1.isPos() << ' ' << neg2.isPos() << ' ' << zero1.isPos() << ' ' << simplify1.isPos() << std::endl;
    std::cout << "Should be: 0 0 0 1\n" << std::endl;

    std::cout << "Testing isNeg =========================" << std::endl;
    std::cout << neg1.isNeg() << ' ' << neg2.isNeg() << ' ' << zero1.isNeg() << ' ' << simplify1.isNeg() << std::endl;
    std::cout << "Should be: 1 1 0 0\n" << std::endl;

    std::cout << "Testing isInf =========================" << std::endl;
    std::cout << neg1.isInf() << ' ' << inf1.isInf() << ' ' << inf2.isInf() << ' ' << inf3.isInf() << std::endl;
    std::cout << "Should be: 0 1 1 1\n" << std::endl;

    std::cout << "Testing reciprocol ====================" << std::endl;
    std::cout << neg1.reciprocol() << ' ' << neg2.reciprocol() << ' ' << simplify5.reciprocol() << std::endl;
    std::cout << "Should be: -1 -2 53/29\n" << std::endl;

    std::cout << "Testing pow ===========================" << std::endl;
    std::cout << simplify4.pow(3) << ' ' << simplify4.pow(-3) << ' ' << neg2.pow(5) << ' ' << neg2.pow(-5) << std::endl;
    std::cout << "Should be: 8 1/8 -1/32 -32\n" << std::endl;

    std::cout << "Testing remainder =====================" << std::endl;
    std::cout << Fraction<int>(10,7).remainder() << ' ' << Fraction<int>(-10, 7).remainder() << std::endl;
    std::cout << "Should be: 3 4\n" << std::endl;

    std::cout << "Testing round =========================" << std::endl;
    std::cout << Fraction<int>(1,4).round() << ' ' << Fraction<int>(2,4).round() << ' ' << Fraction<int>(3,4).round() << ' ' << Fraction<int>(4,4).round() << ' ' << Fraction<int>(-9,4).round() << ' ' << Fraction<int>(-10,4).round() << ' ' << Fraction<int>(-11,4).round() << ' ' << Fraction<int>(12,-4).round() << std::endl;
    std::cout << "Should be: 0 1 1 1 -2 -2 -3 -3\n" << std::endl;


    std::cout << "Testing operator+ =====================" << std::endl;
    std::cout << neg1 + zero1 << ' ' << neg2 + zero2 << ' ' << neg1 + simplify1 << ' ' << simplify4 + simplify5 << std::endl;
    std::cout << "Should be: -1 -1/2 0 135/53\n" << std::endl;

    std::cout << "Testing operator- =====================" << std::endl;
    std::cout << neg1 - zero1 << ' ' << zero1 - neg1 << ' ' << neg2 - zero1 << ' ' << zero1 - neg2 << ' '<< simplify4 - simplify5 << ' ' << simplify5 - simplify4 << std::endl;
    std::cout << "Should be: -1 1 -1/2 1/2 77/53 -77/53\n" << std::endl;

    std::cout << "Testing operator* =====================" << std::endl;
    std::cout << neg1 * zero1 << ' ' << neg1 * neg2 << ' ' << neg1 * simplify4 << ' ' << simplify4 * simplify5 << std::endl;
    std::cout << "Should be: 0 1/2 -2 58/53\n" << std::endl;

    std::cout << "Testing operator/ =====================" << std::endl;
    std::cout << neg1 / zero1 << ' ' << zero1 / neg1 << ' ' << neg1 / neg2 << ' ' << neg2 / neg1 << ' ' << simplify4 / simplify5 << std::endl;
    std::cout << "Should be: -inf 0 2 1/2 106/29\n" << std::endl;

    std::cout << "Testing oporator+= ====================" << std::endl;
    Fraction<int> addOn;
    addOn += zero1;
    std::cout << addOn;
    addOn += neg1;
    std::cout << ' ' << addOn;
    addOn += neg2;
    std::cout << ' ' << addOn;
    addOn += simplify5;
    std::cout << ' ' << addOn << std::endl;
    std::cout << "Should be: 0 -1 -3/2 -101/106\n" << std::endl;

    std::cout << "Testing operator-= ====================" << std::endl;
    Fraction<int> subFrom;
    subFrom -= zero1;
    std::cout << subFrom;
    subFrom -= neg1;
    std::cout << ' ' << subFrom;
    subFrom -= neg2;
    std::cout << ' ' << subFrom;
    subFrom -= simplify5;
    std::cout << ' ' << subFrom << std::endl;
    std::cout << "Should be: 0 1 3/2 101/106\n" << std::endl;

    std::cout << "Testing operator*= ====================" << std::endl;
    Fraction<int> mulTo(1);
    mulTo *= neg1;
    std::cout << mulTo;
    mulTo *= neg2;
    std::cout << ' ' << mulTo;
    mulTo *= simplify4;
    std::cout << ' ' << mulTo;
    mulTo *= zero1;
    std::cout << ' ' << mulTo << std::endl;
    std::cout << "Should be: -1 1/2 1 0\n" << std::endl;

    std::cout << "Testing operator/= ====================" << std::endl;
    Fraction<int> divideFrom(1);
    divideFrom /= neg1;
    std::cout << divideFrom;
    divideFrom /= neg2;
    std::cout << ' ' << divideFrom;
    divideFrom /= simplify4;
    std::cout << ' ' << divideFrom;
    divideFrom /= zero1;
    std::cout << ' ' << divideFrom << std::endl;
    std::cout << "Should be -1 2 1 inf\n" << std::endl;

    std::cout << "Testing operator-() ===================" << std::endl;
    std::cout << -zero1 << ' ' << -neg1 << ' ' << -neg2 << ' ' << -simplify4 << ' ' << -inf1 << std::endl;
    std::cout << "Should be 0 1 1/2 -2 -inf\n" << std::endl;

    std::cout << "Testing operator double ===============" << std::endl;
    std::cout << static_cast<double>(simplify5) << std::endl;
    std::cout << "Should be 0.54717\n" << std::endl;

    return 0;
}
