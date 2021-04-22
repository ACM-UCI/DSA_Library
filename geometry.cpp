//below controls type of data being stored

#include <cmath>

typedef double TYPE;
struct point{
	TYPE x;
	TYPE y;
	friend bool operator==(const point&a, const point&b);
	friend bool operator!=(const point&a, const point&b);
};

bool operator==(const point &a, const point &b){
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const point&a, const point&b){
	return !(a.x==b.x && a.y==b.y);
}

struct point3 {
    TYPE x{},y{},z{};
    point3(TYPE x, TYPE y, TYPE z) : x{x}, y{y}, z{z} { }
    point3(const point &p) : x{p.x}, y{p.y} { }
};

struct gvector{
	point start;
	point end;
	TYPE x;
	TYPE y;

    gvector(TYPE x, TYPE y) : x{x}, y{y} { }

	gvector(point a, point b){
		start = a;
		end = b;
		x = b.x - a.x;
		y = b.y - a.y;
	}

    TYPE dotProduct(const gvector &other) const {
        return x*other.x + y*other.y;
    }

    void scale(TYPE sc) { x *= sc; y *= sc; }
    double magnitude() const { return std::hypot(x, y); }
    double angle() const { return std::atan2(y, x); }

    /*
     * This will only work if TYPE is double
    gvector unitVector() const {
        double mag = magnitude();
        return gvector(x/mag, y/mag);
    }
    */
};

struct g3vector {

    TYPE x{}, y{}, z{};
    g3vector(TYPE x, TYPE y, Type z) : x{x}, y{y}, z{z} { }
    g3vector(const point3 &a, const point3 &b) : x{b.x-a.x}, y{b.y-a.y}, z{b.z-a.z} { } 

    g3vector crossProduct(const g3vector &other) const {
        return g3vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }

    void scale(Type sc) { x *= sc; y *= sc; z *= sc; }
    double magnitude() const { return std::sqrt(x*x + y*y + z*z); }
};

struct line{
	//ax + by = c
	TYPE a;
	TYPE b;
	TYPE c;
};

double angle(TYPE x1, TYPE y1, TYPE x2, TYPE y2, TYPE x3, TYPE y3){
    TYPE vx1 = x1-x2;
    TYPE vy1 = y1-y2;

    TYPE vx2 = x3-x2;
    TYPE vy2 = y3-y2;

    TYPE dot = vx1*vx2 + vy1*vy2;
    TYPE det = vx1*vy2 - vy1*vx2;
    return atan2(det, dot);
}

double angle(point a, point b, point c){
    TYPE vx1 = a.x-b.x;
    TYPE vy1 = a.y-b.y;

    TYPE vx2 = c.x-b.x;
    TYPE vy2 = c.y-b.y;

    TYPE dot = vx1*vx2 + vy1*vy2;
    TYPE det = vx1*vy2 - vy1*vx2;
    return atan2(det, dot);
}

double angle(gvector ab, gvector bc){
	if(ab.start != bc.start)
		return -10000000;
	TYPE dot = ab.x*bc.x + ab.y*bc.y;
	TYPE det = ab.x*bc.y - ab.y*bc.x;
	return atan2(det, dot);
}

void rotateCounterClockwise(double x1, double y1, double x2, double y2, double angle, double &outx, double &outy){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    x1 -= x2;
    y1 -= y2;

    double xnew = x1*c-y1*s;
    double ynew = x1*s+y1*c;
    outx = xnew + x2;
    outy = ynew + y2;
}

void rotateCounterClockwise(point a, point b, double angle, point &out){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    a.x -= b.x;
    a.y -= b.y;

    double xnew = a.x*c-a.y*s;
    double ynew = a.x*s+a.y*c;
    out.x = xnew + b.x;
    out.y = ynew + b.y;
}

point rotateCounterClockwise(point a, point b, double angle){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    a.x -= b.x;
    a.y -= b.y;

    double xnew = a.x*c-a.y*s;
    double ynew = a.x*s+a.y*c;
    return {xnew + b.x, ynew + b.y};
}

void rotateClockwise(double x1, double y1, double x2, double y2, double angle, double &outx, double &outy){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    x1 -= x2;
    y1 -= y2;

    double xnew = x1*c+y1*s;
    double ynew = -x1*s+y1*c;
    outx = xnew + x2;
    outy = ynew + y2;
}

void rotateClockwise(point a, point b, double angle, point &out){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    a.x -= b.x;
    a.y -= b.y;

    double xnew = a.x*c+a.y*s;
    double ynew = -a.x*s+a.y*c;
    out.x = xnew + b.x;
    out.y = ynew + b.y;
}

point rotateClockwise(point a, point b, double angle){
	//rotates x1, y1 around x2, y2
	//angle in radians
    double s = sin(angle);
    double c = cos(angle);

    a.x -= b.x;
    a.y -= b.y;

    double xnew = a.x*c+a.y*s;
    double ynew = -a.x*s+a.y*c;
    return {xnew + b.x, ynew + b.y};
}

point intersection(point a, point b, point c, point d){
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = a1*a.x + b1*a.y;

    double a2 = d.y-c.y;
    double b2 = c.x - d.x;
    double c2 = a2*c.x + b2*c.y;

    double determinant = a1*b2-a2*b1;

    if(determinant == 0){
        return {0,0};
    }else{
        double x = (b2*c1-b1*c2)/determinant;
        double y = (a1*c2-a2*c1)/determinant;
        return {x, y};
    }
}

point intersection(gvector a, gvector b){
    double a1 = a.end.y - a.start.y;
    double b1 = a.start.x - a.end.x;
    double c1 = a1*a.start.x + b1*a.start.y;

    double a2 = b.end.y-b.start.y;
    double b2 = b.start.x - b.end.x;
    double c2 = a2*b.start.x + b2*b.start.y;

    double determinant = a1*b2-a2*b1;

    if(determinant == 0){
        return {0,0};
    }else{
        double x = (b2*c1-b1*c2)/determinant;
        double y = (a1*c2-a2*c1)/determinant;
        return {x, y};
    }
}

point intersection(line a, line b){
	double determinant = a.a*b.b - b.a*a.b;
	if(determinant == 0){
        return {0,0};
    }else{
        double x = (b.b*a.c-a.b*b.c)/determinant;
        double y = (a.a*b.c-b.a*a.c)/determinant;
        return {x, y};
    }
}

bool is_left(TYPE a, TYPE b, TYPE c, TYPE d, TYPE e, TYPE f) {
    double vx = c-a;
    double vy = d-b;

    double _vx = e-a;
    double _vy = f-b;

    return vx * _vy - _vx * vy > 0;
}

bool is_left(gvector a, point b){
	double _vx = b.x-a.start.x;
	double _vy = b.y-a.start.y;

	return a.x*_vy - _vx*a.y > 0;
}

double dist(point a, point b){
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
