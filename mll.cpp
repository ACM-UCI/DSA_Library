#include <iostream>

class mll{
	long long n;
	long long mod;
public:
	mll(long long a = 0, long long b = 1e9+7) : n{a}, mod{b}{};
	friend std::ostream& operator<<(std::ostream& out, const mll& m);
	friend std::istream& operator>>(std::istream& in, mll& m);

	friend mll operator+(const mll &a, const mll &b);
	friend mll operator-(const mll &a, const mll &b);
	friend mll operator*(const mll &a, const mll &b);
	friend mll operator/(const mll &a, const mll &b);
	friend mll operator%(const mll &a, const mll &b);

	friend mll operator+(const mll &a, int b);
	friend mll operator+(int b, const mll &a);
	friend mll operator-(const mll &a, int b);
	friend mll operator-(int b, const mll &a);
	friend mll operator*(const mll &a, int b);
	friend mll operator*(int b, const mll &a);
	friend mll operator/(const mll &a, int b);
	friend mll operator/(int b, const mll &a);
	friend mll operator%(const mll &a, int b);
	friend mll operator%(int b, const mll &a);

	friend mll operator+(const mll &a, long long b);
	friend mll operator+(long long b, const mll &a);
	friend mll operator-(const mll &a, long long b);
	friend mll operator-(long long b, const mll &a);
	friend mll operator*(const mll &a, long long b);
	friend mll operator*(long long b, const mll &a);
	friend mll operator/(const mll &a, long long b);
	friend mll operator/(long long b, const mll &a);
	friend mll operator%(const mll &a, long long b);
	friend mll operator%(long long b, const mll &a);

	//comparisons just based on n
	friend bool operator==(const mll &a, const mll &b);
	friend bool operator!=(const mll &a, const mll &b);
	friend bool operator<(const mll &a, const mll &b);
	friend bool operator>(const mll &a, const mll &b);
	friend bool operator<=(const mll &a, const mll &b);
	friend bool operator>=(const mll &a, const mll &b);

	friend bool operator==(const mll &a, int b);
	friend bool operator==(int b, const mll &a);
	friend bool operator!=(const mll &a, int b);
	friend bool operator!=(int b, const mll &a);
	friend bool operator<(const mll &a, int b);
	friend bool operator<(int b, const mll &a);
	friend bool operator>(const mll &a, int b);
	friend bool operator>(int b, const mll &a);
	friend bool operator<=(const mll &a, int b);
	friend bool operator<=(int b, const mll &a);
	friend bool operator>=(const mll &a, int b);
	friend bool operator>=(int b, const mll &a);

	friend bool operator==(const mll &a, long long b);
	friend bool operator==(long long b, const mll &a);
	friend bool operator!=(const mll &a, long long b);
	friend bool operator!=(long long b, const mll &a);
	friend bool operator<(const mll &a, long long b);
	friend bool operator<(long long b, const mll &a);
	friend bool operator>(const mll &a, long long b);
	friend bool operator>(long long b, const mll &a);
	friend bool operator<=(const mll &a, long long b);
	friend bool operator<=(long long b, const mll &a);
	friend bool operator>=(const mll &a, long long b);
	friend bool operator>=(long long b, const mll &a);

	//prefix
	mll& operator++();
	mll& operator--();
	//postfix
	mll operator++(int);
	mll operator--(int);

	//only adds the n
	mll& operator+=(const mll& a);
	mll& operator-=(const mll& a);
	mll& operator*=(const mll& a);
	mll& operator/=(const mll& a);
	mll& operator%=(const mll& a);

	mll& operator+=(int a);
	mll& operator-=(int a);
	mll& operator*=(int a);
	mll& operator/=(int a);
	mll& operator%=(int a);

	mll& operator+=(long long a);
	mll& operator-=(long long a);
	mll& operator*=(long long a);
	mll& operator/=(long long a);
	mll& operator%=(long long a);


	mll operator-() const;
	mll operator!() const;

	explicit operator bool() const;
	explicit operator int() const;
	explicit operator long long() const;
private:
	long long _inv(long long a) const;
};

long long mll::_inv(long long a) const{
	long long x = 1, y = 0, x1 = 0, y1 = 1, a1 = a, b1 = this->mod;
	while(b1){
		long long q = a1/b1;
		long long t = x;
		x = x1, x1 = t-q*x1;
		t = y;
		y = y1, y1 = t-q*y1;
		t = a1;
		a1 = b1, b1 = a1-q*b1;
	}
	return (x%this->mod + mod)%this->mod;
}

std::ostream& operator<<(std::ostream& out, const mll& m){
	out << m.n;
	return out;
}

std::istream& operator>>(std::istream& in, mll& m){
	in >> m.n;
	m.n %= m.mod;
	return in;
}

mll operator+(const mll &a, const mll &b){
	//both mll must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mll(((a.n+b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mll operator-(const mll &a, const mll &b){
	//both mll must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mll(((a.n-b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mll operator*(const mll &a, const mll &b){
	//both mll must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mll(((a.n*b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mll operator/(const mll &a, const mll &b){
	//both mll must have the same modulus
	if(a.mod != b.mod)
		throw 1;

	return mll(((a.n*(b._inv(b.n)))%a.mod+a.mod)%a.mod, a.mod);
}

mll operator%(const mll &a, const mll &b){
	//no TrUe mathematical meaning
	//just does a blind a.n % b.n
	return mll(a.n%b.n, a.mod);
}

mll operator+(const mll &a, int b){
	return mll(((a.n+b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator+(int b, const mll &a){ return a + b; }
mll operator-(const mll &a, int b){
	return mll(((a.n-b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator-(int b, const mll &a){ return a - b; }
mll operator*(const mll &a, int b){
	return mll(((a.n*b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator*(int b, const mll &a){ return a*b; }
mll operator/(const mll &a, int b){
	return mll(((a.n*a._inv(b))%a.mod + a.mod)%a.mod, a.mod);
}
mll operator/(int b, const mll &a){
	return mll(((b*a._inv(a.n))%a.mod+a.mod)%a.mod, a.mod);
}
mll operator%(const mll &a, int b){
	return mll(((a.n%b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator%(int b, const mll &a){
	return mll(((b%a.n)%a.mod + a.mod)%a.mod, a.mod);
}


mll operator+(const mll &a, long long b){
	return mll(((a.n+b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator+(long long b, const mll &a){ return a + b; }
mll operator-(const mll &a, long long b){
	return mll(((a.n-b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator-(long long b, const mll &a){ return a - b; }
mll operator*(const mll &a, long long b){
	return mll(((a.n*b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator*(long long b, const mll &a){ return a*b; }
mll operator/(const mll &a, long long b){
	return mll(((a.n*a._inv(b))%a.mod + a.mod)%a.mod, a.mod);
}
mll operator/(long long b, const mll &a){
	return mll(((b*a._inv(a.n))%a.mod+a.mod)%a.mod, a.mod);
}
mll operator%(const mll &a, long long b){
	return mll(((a.n%b)%a.mod + a.mod)%a.mod, a.mod);
}
mll operator%(long long b, const mll &a){
	return mll(((b%a.n)%a.mod + a.mod)%a.mod, a.mod);
}

mll mll::operator-() const{
	return mll(-this->n + this->mod, this->mod);
}
mll mll::operator!() const{
	return mll(!(this->n), this->mod);
}

mll::operator bool() const{
	return !!(this->n);
}
mll::operator int() const{
	return this->n;
}
mll::operator long long() const{
	return (long long)this->n;
}

bool operator==(const mll &a, const mll &b){ return a.n == b.n; }
bool operator!=(const mll &a, const mll &b){ return a.n != b.n; }
bool operator<(const mll &a, const mll &b){ return a.n < b.n; }
bool operator>(const mll &a, const mll &b){return a.n > b.n; }
bool operator<=(const mll &a, const mll &b){return a.n <= b.n; }
bool operator>=(const mll &a, const mll &b){return a.n >= b.n; }

bool operator==(const mll &a, int b){ return a.n == b; }
bool operator==(int b, const mll &a){ return b == a.n; }
bool operator!=(const mll &a, int b){ return a.n != b; }
bool operator!=(int b, const mll &a){ return b != a.n; }
bool operator<(const mll &a, int b){ return a.n < b; }
bool operator<(int b, const mll &a){ return b < a.n; }
bool operator>(const mll &a, int b){ return a.n > b; }
bool operator>(int b, const mll &a){ return b > a.n; }
bool operator<=(const mll &a, int b){ return a.n <= b; }
bool operator<=(int b, const mll &a){ return b <= a.n; }
bool operator>=(const mll &a, int b){ return a.n >= b; }
bool operator>=(int b, const mll &a){ return b >= a.n; }

bool operator==(const mll &a, long long b){ return a.n == b; }
bool operator==(long long b, const mll &a){ return b == a.n; }
bool operator!=(const mll &a, long long b){ return a.n != b; }
bool operator!=(long long b, const mll &a){ return b != a.n; }
bool operator<(const mll &a, long long b){ return a.n < b; }
bool operator<(long long b, const mll &a){ return b < a.n; }
bool operator>(const mll &a, long long b){ return a.n > b; }
bool operator>(long long b, const mll &a){ return b > a.n; }
bool operator<=(const mll &a, long long b){ return a.n <= b; }
bool operator<=(long long b, const mll &a){ return b <= a.n; }
bool operator>=(const mll &a, long long b){ return a.n >= b; }
bool operator>=(long long b, const mll &a){ return b >= a.n; }


mll& mll::operator++(){
	(this->n)++;
	this->n %= this->mod;
	return *this;
}
mll mll::operator++(int){
	mll temp(*this);
	++(this->n);
	return temp;
}
mll& mll::operator--(){
	(this->n)--;
	this->n %= this->mod;
	return *this;
}
mll mll::operator--(int){
	mll temp(*this);
	--(this->n);
	return temp;
}


mll& mll::operator+=(const mll& a){
	this->n += a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator-=(const mll& a){
	this->n -= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator*=(const mll& a){
	this->n *= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator/=(const mll& a){
	this->n *= this->_inv(a.n);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator%=(const mll& a){
	this->n %= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}

mll& mll::operator+=(int a){
	this->n += a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator-=(int a){
	this->n -= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator*=(int a){
	this->n *= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator/=(int a){
	this->n *= this->_inv(a);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator%=(int a){
	this->n %= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}

mll& mll::operator+=(long long a){
	this->n += a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator-=(long long a){
	this->n -= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator*=(long long a){
	this->n *= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator/=(long long a){
	this->n *= this->_inv(a);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mll& mll::operator%=(long long a){
	this->n %= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}