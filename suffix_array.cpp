#include <bits/stdc++.h>

// = BEGIN SUFFIX ARRAY ==============================================
//     * All global variables will be initially unset, this must manually be done
//     * This file is structured such that it gives maximum flexibility to the user
//     * The standard procedure is as follows:
//     	1. set SuffixArray::size and SuffixArray::str
//     	2. call buildSA()
//     	3. call buildLCP() -> if needed
//     * queries on SuffixArray::SA must manually be done
//     * A simple segment tree will be provided for RMQ on LCP for longest common prefix
namespace SuffixArray {

	
	// === DECLARE GLOBAL VARIABLES ================================
	int size;					// size: the length of the string
	std::vector<int> SA, RA;	// SA: the suffix array | RA: the rank array
	std::vector<int> LCP;		// LCP: longest common prefix
	std::string str;			// str: the original string
	// === END GLOBAL VARIABLES ====================================



	// === DEFINE FUNCTION PROFILES ================================
	void buildSA();
		// Description:
		// 	Constructs the SA and RA from scratch
		// Requirements:
		// 	1. SuffixArray::str and Suffixarray::size are initialized

	void countSort(int);
		// Description:
		// 	Sorts SA by the kth indice after i (will only make sense if you understand how suffix arrays are built)
		// 	Basically like a radix sort
		// 	Used by buildSA()
	
	void rank(int);
		// Description
		// 	Reranks the array
		// 	Will be called by buildSA() after countSort is called
	
	void buildLCP();
		// Description
		// 	Determines the longest common prefix between each sorted suffix
		// 	Can be used with an RMQ algorithm for efficiently finding LCP between any two suffixes
		// Requirements
		// 	SA must be completely built before calling
	
	// ===== DEBUGGING FUNCTIONS =================================
	void printSA();
	void printRA();
	void printLCP();
	void printVector(const std::vector<int>& v);
	// ===== END DEBUGGING FUNCTIONS =============================
	
	// === END FUNCTION PROFILES ===================================



	// === DEFINE FUNCTION IMPLEMENTATIONS =========================
	void buildSA() {
		
		// initialize data
		SA.assign(size,0);
		RA.assign(size,0);
		for (int i = 0; i < size; ++i) {
			SA[i] = i;
			RA[i] = str[i];
		}

		for (int i = 0; (1<<i) <= size; ++i) {
			countSort(1<<i);	// First sort SA[i+k]
			countSort(0);		// Then stable sort by SA[i]

			rank(1<<i);			// rerank 

			if (RA[SA[size-1]] == size-1) break;	// Time saving trick
		}

	}

	void countSort(int k) {
		int maxi = std::max(300, size);	// 300 because that captures an entire byte (1 char) plus more
		std::vector<int> buckets(maxi);
		for (int i = 0; i < size; ++i) {	// Count occurences of each rank
			++buckets[RA[(SA[i]+k)%size]];
		}

		int sum = 0;
		for (int i = 0; i < maxi; ++i) {	// compute cumulative sums
			int temp = buckets[i];
			buckets[i] = sum;
			sum += temp;
		}

		std::vector<int> tSA = SA;
		for (int i = 0; i < size; ++i) {	// Resorts the array based on the updated rank of each suffix
			int newRank = buckets[RA[(tSA[i]+k)%size]]++;
			SA[newRank] = tSA[i];
		}
	}

	void rank(int k) {
		std::vector<int> tRA = RA;
		int r = RA[SA[0]] = 0;
		for (int i = 1; i < size; ++i) {

			// The following increments r if suffix SA[i] can be determined to be lexicographically greater than SA[i-1]
			if ( tRA[SA[i]] != tRA[SA[i-1]]  ||  tRA[(SA[i]+k)%size] != tRA[(SA[i-1]+k)%size] ) {
				++r;
			}

			RA[SA[i]] = r;
		}
	}

	void buildLCP() {
		LCP.assign(size-1,0);

		// The following takes advantage of the fact that the LCP(suffix-1, suffix) will be at most one larger than LCP(suffix, suffix+1)
		int currMatch = 0;
		for (int suffix = 0; suffix < size-1; ++suffix) {	// suffix indexes the original string, indexing RA[suffix] gives the ordering of that suffix
			int suffixAbove = SA[RA[suffix] - 1];	// index of the suffix ranked before SA[suffix]

			while (std::max(suffix, suffixAbove)+currMatch < size && str[suffix+currMatch] == str[suffixAbove+currMatch]) {
				++currMatch;
			}
			LCP[RA[suffixAbove]] = currMatch;
			currMatch = std::max(0, currMatch-1);
		}
	}

	void printSA() { printVector(SA); }
	void printRA() { printVector(RA); }
	void printLCP() { printVector(LCP); }
	
	void printVector(const std::vector<int>& v) {
		if (v.size() > 0) {
			printf("%d", v[0]);
			for (int i = 1; i < v.size(); ++i) {
				printf(" %d", v[i]);
			} printf("\n");
		}
	}
	// === END FUNCTION IMPLEMENTATIONS ============================
	

} // end namespace
// = END SUFFIX ARRAY ================================================


int main() {

//	The following is an example workflow to compute and print out the suffix array and the longest common prefix
//	std::cin >> SuffixArray::str;
//	SuffixArray::str += '$';
//	SuffixArray::size = SuffixArray::str.length();
//	SuffixArray::buildSA();
//	SuffixArray::buildLCP();
//	SuffixArray::printSA();
//	SuffixArray::printLCP();

	return 0;
}
