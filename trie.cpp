#include <bits/stdc++.h>



class Trie {

private:
	
	struct SegTree {

		int size;
		std::vector<int> st;	// stores index and value
		int def;

		static int left(int x) { return (x<<1) + 1; }
		static int right(int x) { return (x<<1) + 2; }
		static int mid(int l, int r) { return (r-l)/2 + l; }


		void init(int n, int defaultValue) {
			def = defaultValue;
			size = 1;
			while (size < n) { size = (size<<1); }
			st.assign(size<<1, def);
		}

		void build(std::vector<int>& arr, int x, int lx, int rx) {
			if (rx-lx == 1) {
				if (lx < arr.size()) {
					st[x] = arr[lx];
				}
				return;
			}

			int mx = SegTree::mid(lx,rx);
			build(arr, SegTree::left(x), lx, mx);
			build(arr, SegTree::right(x), mx, rx);
			st[x] = std::min(st[SegTree::left(x)], st[SegTree::right(x)]);
		}

		void build(std::vector<int>& arr) {
			build(arr, 0, 0, size);
		}

		// We only care about the depth
		int rmq(int l, int r, int x, int lx, int rx) {
			if (rx <= l || r <= lx) {
				return def;
			} else if (l <= lx && rx <= r) {
				return st[x];
			} else {
				int mx = SegTree::mid(lx,rx);
				int res1 = rmq(l, r, SegTree::left(x), lx, mx);
				int res2 = rmq(l, r, SegTree::right(x), mx, rx);
				return std::min(res1, res2);
			}
		}

		// Simply returns the depth of the LCA
		int rmq(int l, int r) {
			return rmq(l, r, 0, 0, size);
		}

	};


	struct TrieNode {
		bool is_word;
		int nodeID;
		TrieNode* children[26];

		TrieNode(int id) : is_word{false}, nodeID{id} {
			for (int i = 0; i < 26; ++i) {
				children[i] = nullptr;
			}
		}
	};

	static void destroyTrie(TrieNode* curr) {
		for (int i = 0; i < 26; ++i) if (curr->children[i] != nullptr) {
			destroyTrie(curr->children[i]);
		}
		delete curr;
	}

	TrieNode* root;
	int numNodes;


	// For LCA - copied from Halim
	std::vector<int> L;		// Records depth of each recorded node
	std::vector<int> H;		// H[i] is index of first occurrence of node i in E
	std::vector<int> E;		// Sequence of visited nodes
	int idx;
	SegTree st;

	// DFS to build the RMQ on the LCA	- copied from Halim
	void buildLCA(TrieNode* curr, int depth) {
		H[curr->nodeID] = idx;
		E[idx] = curr->nodeID;
		L[idx++] = depth;

		// iterate through children of curr
		for (int i = 0; i < 26; ++i) if (curr->children[i] != nullptr) {
			buildLCA(curr->children[i], depth+1);
			E[idx] = curr->nodeID;
			L[idx++] = depth;
		}
	}

public:
	Trie() : root{new TrieNode(0)}, numNodes{1}{
		// No implementation required
	}

	~Trie() {
		destroyTrie(root);
	}

	// Adds the word to the prefix trie
	// Returns the id of the node corresponding to the end of the word
	int addWord(std::string& word) {
		TrieNode* curr = root;
		
		for (int i = 0; i < word.length(); ++i) {
			if (curr->children[word[i]-'a'] == nullptr) {
				curr->children[word[i]-'a'] = new TrieNode(numNodes++);
			}
			curr = curr->children[word[i]-'a'];
		}

		curr->is_word = true;
		return curr->nodeID;
	}

	// returns the id corresponding to this word, -1 if it doesnt exist
	int getWordID(std::string& word) {
		TrieNode* curr = root;

		for (int i = 0; i < word.length(); ++i) {
			if (curr->children[word[i]-'a'] == nullptr) {
				return -1;
			}
			curr = curr->children[word[i]-'a'];
		}

		return curr->is_word ? curr->nodeID : -1;
	}

	void buildLCA() {
		idx = 0;
		L.assign(numNodes<<1, 0);
		H.assign(numNodes<<1, -1);
		E.assign(numNodes<<1, 0);
		buildLCA(root, 0);

		st.init(L.size(), std::numeric_limits<int>::max());
		st.build(L);
	}

	// Returns the longest common prefix between any two strings in the Trie if their nodeIDs are known
	int LCP(int nodeID1, int nodeID2) {
		int hu = H[nodeID1];
		int hv = H[nodeID2];
		if (hu > hv) std::swap(hu,hv);

		return st.rmq(hu, hv+1);	// returns the index of the lcp
	}
	
};

int main() {


	return 0;
}
