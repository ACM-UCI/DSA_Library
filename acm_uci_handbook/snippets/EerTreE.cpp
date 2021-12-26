#include <array>
#include <string>

class EerTreE {
private:
    struct Node {
        Node *suf;
        std::array<Node *, 256> lab;
        int len;
        Node(int len) : suf{nullptr}, len{len} {
            std::fill(std::begin(lab), std::end(lab), nullptr);
        }
    };

    void deconstruct(Node *curr) {
        for (Node *child : curr->lab) if (child != nullptr)
            deconstruct(child);
        delete curr;
    }

public:
    Node *root1, *root2, *current;
    int i, cnt; // cnt is number of unique palindromes
    std::string s;

    EerTreE() : i{0}, cnt{0}, s{""} {
        root1 = new Node(-1);
        root1->suf = root1;
        root2 = new Node(0);
        root2->suf = root1;
        current = root2;
    }

    ~EerTreE() {
        deconstruct(root1);
        deconstruct(root2);
    }
    
    void append(char c) {
        s += c;
        Node *cur = current;
        while (i - 1 - cur->len < 0 || s[i-1-cur->len] != c)
            cur = cur->suf;
        
        if (cur->lab[c] == nullptr) {
            ++cnt;
            Node *tmp = new Node(cur->len + 2);
            cur->lab[c] = tmp;
            
            if (tmp->len == 1) {
                tmp->suf = root2;
                current = tmp;
            } else {
                cur = cur->suf;
                while (i - 1 - cur->len < 0 || s[i-1-cur->len] != c)
                    cur = cur->suf;
                tmp->suf = cur->lab[c];
                current = tmp;
            }
        } else {
            current = cur->lab[c];
        }
        
        ++i;
    }
    
    class Iterator {
    private:
        Node *cur;
    public:
        Iterator(Node *curnode) : cur{curnode} { }
        int operator*() { return cur->len; }
        Iterator &operator++() { cur = cur->suf; return *this; }
        bool operator==(const Iterator &other) { return cur == other.cur; }
        bool operator!=(const Iterator &other) { return cur != other.cur; }
    };
    
    EerTreE::Iterator begin() { return Iterator(current); }
    EerTreE::Iterator end() { return Iterator(root1); }
};
