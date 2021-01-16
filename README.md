# Competitive Programming Data Structures and Algorithms

## About
Contains a library of premade templates for common data structures and algorithms found in competitive programming

## Data Structures

### Segment Tree
* About Segment Trees
	* Use for queries over ranges of data
		* Operations on said ranges must be associative

* Functionality
	* Builds from arr O(N)
	* Updates individual values O(logN)
	* Queries on associative range O(logN)
	* Prints debug elements O(N)
	* Does not currently support lazy propagation
* segment_tree.cpp
	* Declare with c++ template
		* e.g. `SegTree<long long> seg_tree(size, default, associativeFunction);`
	* Debug print requires declared template type supports `<<` insertion operator
		* Stream io with `<<` is slower than `stdio.h` in C++ so be careful with using this everywhere
	
* segment_tree.py
	* Note that this class has not been optimized for maximized efficiency
		* All that can be promised is operations in accordance with the previously defined runtime complexities

---

### Suffix Array

---

### reTrieval Tree

---

### Union Find

---

### Matrix
* Work in conjunction with Floyd Warshalls

---
