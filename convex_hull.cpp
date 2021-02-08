#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>


namespace ConvexHull {

	template <typename T>
	struct Point {
		T x,y;

		bool operator<(const Point<T>& other) const {
			return (x == other.x) ? y < other.y : x < other.x;
		}

		bool operator==(const Point<T>& other) const {
			return x == other.x && y == other.y;
		}
	};

	template <typename T>
	struct Vector {
		T x,y;
	};

	template <typename T>
	T isccw(Vector<T>& a, Vector<T>& b) {
		return a.x*b.y - a.y*b.x;
	}

	template <typename T>
	void buildHull(std::vector<Point<T>>& hull, std::vector<Point<T>>& points, bool ccw) {
		for (Point<T>& p : points) {
			while (hull.size() >= 2) {
				Point<T>& a = hull[hull.size() - 2];
				Point<T>& b = hull[hull.size() - 1];
				Point<T>& c = p;
				Vector<T> v1 = Vector<T>{b.x-a.x, b.y-a.y};
				Vector<T> v2 = Vector<T>{c.x-b.x, c.y-b.y};

				if (ccw && isccw<T>(v1, v2) > 0) {
					break;
				} else if (!ccw && isccw<T>(v1, v2) < 0) {
					break;
				}

				hull.pop_back();
			}

			while (!hull.empty() && p == hull.back()) {
				hull.pop_back();
			}

			hull.push_back(p);
		}
	}
	
	template <typename T>
	void buildConvexHull(std::vector<Point<T>>& points, std::vector<Point<T>>& convex_hull) {
		std::sort(points.begin(), points.end());
		std::vector<Point<T>> lower_hull, upper_hull;
		buildHull<T>(lower_hull, points, true);
		buildHull<T>(upper_hull, points, false);

		convex_hull.assign(lower_hull.size() + std::max(0, (int) upper_hull.size()-2), Point<T>{0,0});
		int j = 0;
		for (int i = 0; i < lower_hull.size(); ++i,++j) {
			convex_hull[j] = lower_hull[i];
		}
		for (int i = upper_hull.size()-2; i > 0; --i,++j) {
			convex_hull[j] = upper_hull[i];
		}
	}
}

int main() {

	int N;
	while (scanf("%d", &N), N) {
		std::vector<ConvexHull::Point<int>> points(N);
		std::vector<ConvexHull::Point<int>> convex_hull;
		for (int i = 0; i < N; ++i) {
			int x, y; scanf("%d %d", &x, &y);
			points[i] = ConvexHull::Point<int>{x, y};
		}

		ConvexHull::buildConvexHull<int>(points, convex_hull);

		printf("%d\n", convex_hull.size());
		for (const ConvexHull::Point<int>& p : convex_hull) {
			printf("%d %d\n", p.x, p.y);
		}
	}

	return 0;
}
