#include <iostream>

class mint{
	int n;
	int mod;
public:
	mint(int a = 0, int b = 1e9+7) : n{a}, mod{b}{};
	friend std::ostream& operator<<(std::ostream& out, const mint& m);
	friend std::istream& operator>>(std::istream& in, mint& m);

	friend mint operator+(const mint &a, const mint &b);
	friend mint operator-(const mint &a, const mint &b);
	friend mint operator*(const mint &a, const mint &b);
	friend mint operator/(const mint &a, const mint &b);
	friend mint operator%(const mint &a, const mint &b);

	friend mint operator+(const mint &a, int b);
	friend mint operator+(int b, const mint &a);
	friend mint operator-(const mint &a, int b);
	friend mint operator-(int b, const mint &a);
	friend mint operator*(const mint &a, int b);
	friend mint operator*(int b, const mint &a);
	friend mint operator/(const mint &a, int b);
	friend mint operator/(int b, const mint &a);
	friend mint operator%(const mint &a, int b);
	friend mint operator%(int b, const mint &a);

	friend mint operator+(const mint &a, long long b);
	friend mint operator+(long long b, const mint &a);
	friend mint operator-(const mint &a, long long b);
	friend mint operator-(long long b, const mint &a);
	friend mint operator*(const mint &a, long long b);
	friend mint operator*(long long b, const mint &a);
	friend mint operator/(const mint &a, long long b);
	friend mint operator/(long long b, const mint &a);
	friend mint operator%(const mint &a, long long b);
	friend mint operator%(long long b, const mint &a);

	//comparisons just based on n
	friend bool operator==(const mint &a, const mint &b);
	friend bool operator!=(const mint &a, const mint &b);
	friend bool operator<(const mint &a, const mint &b);
	friend bool operator>(const mint &a, const mint &b);
	friend bool operator<=(const mint &a, const mint &b);
	friend bool operator>=(const mint &a, const mint &b);

	friend bool operator==(const mint &a, int b);
	friend bool operator==(int b, const mint &a);
	friend bool operator!=(const mint &a, int b);
	friend bool operator!=(int b, const mint &a);
	friend bool operator<(const mint &a, int b);
	friend bool operator<(int b, const mint &a);
	friend bool operator>(const mint &a, int b);
	friend bool operator>(int b, const mint &a);
	friend bool operator<=(const mint &a, int b);
	friend bool operator<=(int b, const mint &a);
	friend bool operator>=(const mint &a, int b);
	friend bool operator>=(int b, const mint &a);

	friend bool operator==(const mint &a, long long b);
	friend bool operator==(long long b, const mint &a);
	friend bool operator!=(const mint &a, long long b);
	friend bool operator!=(long long b, const mint &a);
	friend bool operator<(const mint &a, long long b);
	friend bool operator<(long long b, const mint &a);
	friend bool operator>(const mint &a, long long b);
	friend bool operator>(long long b, const mint &a);
	friend bool operator<=(const mint &a, long long b);
	friend bool operator<=(long long b, const mint &a);
	friend bool operator>=(const mint &a, long long b);
	friend bool operator>=(long long b, const mint &a);

	//prefix
	mint& operator++();
	mint& operator--();
	//postfix
	mint operator++(int);
	mint operator--(int);

	//only adds the n
	mint& operator+=(const mint& a);
	mint& operator-=(const mint& a);
	mint& operator*=(const mint& a);
	mint& operator/=(const mint& a);
	mint& operator%=(const mint& a);

	mint& operator+=(int a);
	mint& operator-=(int a);
	mint& operator*=(int a);
	mint& operator/=(int a);
	mint& operator%=(int a);

	mint& operator+=(long long a);
	mint& operator-=(long long a);
	mint& operator*=(long long a);
	mint& operator/=(long long a);
	mint& operator%=(long long a);


	mint operator-() const;
	mint operator!() const;

	explicit operator bool() const;
	explicit operator int() const;
	explicit operator long long() const;
private:
	int _inv(int a) const;
};

int mint::_inv(int a) const{
	int x = 1, y = 0, x1 = 0, y1 = 1, a1 = a, b1 = this->mod;
	while(b1){
		int q = a1/b1;
		int t = x;
		x = x1, x1 = t-q*x1;
		t = y;
		y = y1, y1 = t-q*y1;
		t = a1;
		a1 = b1, b1 = a1-q*b1;
	}
	return (x%this->mod + mod)%this->mod;
}

std::ostream& operator<<(std::ostream& out, const mint& m){
	out << m.n;
	return out;
}

std::istream& operator>>(std::istream& in, mint& m){
	in >> m.n;
	m.n %= m.mod;
	return in;
}

mint operator+(const mint &a, const mint &b){
	//both mint must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mint(((a.n+b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mint operator-(const mint &a, const mint &b){
	//both mint must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mint(((a.n-b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mint operator*(const mint &a, const mint &b){
	//both mint must have the same modulus
	if(a.mod != b.mod)
		throw 1;
	return mint(((a.n*b.n)%a.mod+a.mod)%a.mod, a.mod);
}

mint operator/(const mint &a, const mint &b){
	//both mint must have the same modulus
	if(a.mod != b.mod)
		throw 1;

	return mint(((a.n*(b._inv(b.n)))%a.mod+a.mod)%a.mod, a.mod);
}

mint operator%(const mint &a, const mint &b){
	//no TrUe mathematical meaning
	//just does a blind a.n % b.n
	return mint(a.n%b.n, a.mod);
}

mint operator+(const mint &a, int b){
	return mint(((a.n+b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator+(int b, const mint &a){ return a + b; }
mint operator-(const mint &a, int b){
	return mint(((a.n-b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator-(int b, const mint &a){ return a - b; }
mint operator*(const mint &a, int b){
	return mint(((a.n*b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator*(int b, const mint &a){ return a*b; }
mint operator/(const mint &a, int b){
	return mint(((a.n*a._inv(b))%a.mod + a.mod)%a.mod, a.mod);
}
mint operator/(int b, const mint &a){
	return mint(((b*a._inv(a.n))%a.mod+a.mod)%a.mod, a.mod);
}
mint operator%(const mint &a, int b){
	return mint(((a.n%b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator%(int b, const mint &a){
	return mint(((b%a.n)%a.mod + a.mod)%a.mod, a.mod);
}


mint operator+(const mint &a, long long b){
	return mint(((a.n+b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator+(long long b, const mint &a){ return a + b; }
mint operator-(const mint &a, long long b){
	return mint(((a.n-b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator-(long long b, const mint &a){ return a - b; }
mint operator*(const mint &a, long long b){
	return mint(((a.n*b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator*(long long b, const mint &a){ return a*b; }
mint operator/(const mint &a, long long b){
	return mint(((a.n*a._inv(b))%a.mod + a.mod)%a.mod, a.mod);
}
mint operator/(long long b, const mint &a){
	return mint(((b*a._inv(a.n))%a.mod+a.mod)%a.mod, a.mod);
}
mint operator%(const mint &a, long long b){
	return mint(((a.n%b)%a.mod + a.mod)%a.mod, a.mod);
}
mint operator%(long long b, const mint &a){
	return mint(((b%a.n)%a.mod + a.mod)%a.mod, a.mod);
}

mint mint::operator-() const{
	return mint(-this->n + this->mod, this->mod);
}
mint mint::operator!() const{
	return mint(!(this->n), this->mod);
}

mint::operator bool() const{
	return !!(this->n);
}
mint::operator int() const{
	return this->n;
}
mint::operator long long() const{
	return (long long)this->n;
}

bool operator==(const mint &a, const mint &b){ return a.n == b.n; }
bool operator!=(const mint &a, const mint &b){ return a.n != b.n; }
bool operator<(const mint &a, const mint &b){ return a.n < b.n; }
bool operator>(const mint &a, const mint &b){return a.n > b.n; }
bool operator<=(const mint &a, const mint &b){return a.n <= b.n; }
bool operator>=(const mint &a, const mint &b){return a.n >= b.n; }

bool operator==(const mint &a, int b){ return a.n == b; }
bool operator==(int b, const mint &a){ return b == a.n; }
bool operator!=(const mint &a, int b){ return a.n != b; }
bool operator!=(int b, const mint &a){ return b != a.n; }
bool operator<(const mint &a, int b){ return a.n < b; }
bool operator<(int b, const mint &a){ return b < a.n; }
bool operator>(const mint &a, int b){ return a.n > b; }
bool operator>(int b, const mint &a){ return b > a.n; }
bool operator<=(const mint &a, int b){ return a.n <= b; }
bool operator<=(int b, const mint &a){ return b <= a.n; }
bool operator>=(const mint &a, int b){ return a.n >= b; }
bool operator>=(int b, const mint &a){ return b >= a.n; }

bool operator==(const mint &a, long long b){ return a.n == b; }
bool operator==(long long b, const mint &a){ return b == a.n; }
bool operator!=(const mint &a, long long b){ return a.n != b; }
bool operator!=(long long b, const mint &a){ return b != a.n; }
bool operator<(const mint &a, long long b){ return a.n < b; }
bool operator<(long long b, const mint &a){ return b < a.n; }
bool operator>(const mint &a, long long b){ return a.n > b; }
bool operator>(long long b, const mint &a){ return b > a.n; }
bool operator<=(const mint &a, long long b){ return a.n <= b; }
bool operator<=(long long b, const mint &a){ return b <= a.n; }
bool operator>=(const mint &a, long long b){ return a.n >= b; }
bool operator>=(long long b, const mint &a){ return b >= a.n; }


mint& mint::operator++(){
	(this->n)++;
	this->n %= this->mod;
	return *this;
}
mint mint::operator++(int){
	mint temp(*this);
	++(this->n);
	return temp;
}
mint& mint::operator--(){
	(this->n)--;
	this->n %= this->mod;
	return *this;
}
mint mint::operator--(int){
	mint temp(*this);
	--(this->n);
	return temp;
}


mint& mint::operator+=(const mint& a){
	this->n += a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator-=(const mint& a){
	this->n -= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator*=(const mint& a){
	this->n *= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator/=(const mint& a){
	this->n *= this->_inv(a.n);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator%=(const mint& a){
	this->n %= a.n;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}

mint& mint::operator+=(int a){
	this->n += a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator-=(int a){
	this->n -= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator*=(int a){
	this->n *= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator/=(int a){
	this->n *= this->_inv(a);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator%=(int a){
	this->n %= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}

mint& mint::operator+=(long long a){
	this->n += a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator-=(long long a){
	this->n -= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator*=(long long a){
	this->n *= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator/=(long long a){
	this->n *= this->_inv(a);
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}
mint& mint::operator%=(long long a){
	this->n %= a;
	this->n = (this->n%this->mod + this->mod)%this->mod;
	return *this;
}