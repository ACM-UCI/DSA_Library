#include <array>
#include <string>
class Trie {
private:
    class Node {
    public:
        bool isWord;
        std::array<Node *, 256> c;
        Node() : isWord{false} {
            std::fill(std::begin(c), std::end(c), nullptr);
        }
    };
    
    Node *root;
    
    void deconstruct(Node *curr) {
        for (Node *child : curr->c) if (child != nullptr) deconstruct(child);
        delete curr;
    }
public:
    Trie() : root{new Node()} { }
    
    ~Trie() {
        deconstruct(root);
    }
    
    void insert(const std::string &word) {
        Node *curr = root;
        for (char c : word) {
            curr = curr->c[c] == nullptr ? 
                (curr->c[c] = new Node()) : curr->c[c];
        }
        curr->isWord = true;
    }
    
    bool search(const std::string &word) const {
        Node *curr = root;
        for (char c : word)
            if (curr->c[c] == nullptr) return false;
            else curr = curr->c[c];
        return curr->isWord;
    }
    
    bool startsWith(string prefix) const {
        Node *curr = root;
        for (char c : prefix)
            if (curr->c[c] == nullptr) return false;
            else curr = curr->c[c];
        return true;
    }
};
