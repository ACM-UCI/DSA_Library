#include <bits/stdc++.h>

template <typename T>
class SegTree {
using AssociativeFunc = std::function<T (T&,T&)>;
private:

	static int left(int x) { return (x<<1) + 1; }
	static int right(int x) { return (x<<1) + 2; }
	static int mid(int l, int r) { return (r-l)/2 + l; }

	int size;			// width of the segment tree
	T defValue;			// default value used in the seg tree
	AssociativeFunc f;	// associative function that combines two segments
	std::vector<T> st;	// Stores the seg tree

	void build(std::vector<T>& a, int x, int lx, int rx) {
		if (rx-lx == 1) {
			if (lx < a.size()) {
				st[x] = a[lx];
			}
			return;
		} else {
			int mx = SegTree::mid(lx,rx);
			build(a, SegTree::left(x), lx, mx);
			build(a, SegTree::right(x), mx, rx);

			st[x] = f(st[SegTree::left(x)], st[SegTree::right(x)]);
		}
	}

	void set(int i, T v, int x, int lx, int rx) {
		if (rx-lx == 1) {
			st[x] = v;
			return;
		}

		int mx = SegTree::mid(lx,rx);
		if (i < mx) {
			set(i, v, SegTree::left(x), lx, mx);
		} else {
			set(i, v, SegTree::right(x), mx, rx);
		}

		st[x] = f(st[SegTree::left(x)], st[SegTree::right(x)]);
	}

	T rangeQuery(int l, int r, int x, int lx, int rx) {
		if (rx <= l || r <= lx) {
			return defValue;
		} else if (l <= lx && rx <= r) {
			return st[x];
		} else {
			int mx = SegTree::mid(lx,rx);
			
			T res1 = rangeQuery(l, r, SegTree::left(x), lx, mx);
			T res2 = rangeQuery(l, r, SegTree::right(x), mx, rx);
			return f(res1, res2);
		}
	}

	void debugPrintElements(int x, int lx, int rx) {
		if (rx-lx == 1) {
			std::cout << st[x] << ',';
			return;
		}

		int mx = SegTree::mid(lx, rx);
		debugPrintElements(SegTree::left(x), lx, mx);
		debugPrintElements(SegTree::right(x), mx, rx);
	}

public:
	SegTree(int numElements, T defaultValue, AssociativeFunc funct) 
	:defValue{defaultValue}, f{funct} {
		size = 1;
		while (size < numElements) { size = (size<<1); }
		st.assign(size<<1, defaultValue);
	}

	void build(std::vector<T>& elements) {
		build(elements, 0, 0, size);
	}

	void set(int i, T v) {
		set(i, v, 0, 0, size);
	}

	T rangeQuery(int l, int r) {
		return rangeQuery(l, r, 0, 0, size);
	}

	void debugPrintElements() {
		debugPrintElements(0, 0, size);
		std::cout << std::endl;
	}

};


int main() {


	return 0;
}
