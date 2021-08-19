#include <array>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <utility>
#include <algorithm>

class AhoTrie {
public:
    struct Node {
        std::array<Node *, 26> children;
        Node *failure;
        Node *output;
        int outputIndex;

        Node() : failure{nullptr}, output{nullptr}, outputIndex{-1} {
            std::fill(std::begin(children), std::end(children), nullptr);
        }
    };

private:
    Node *root;
    std::vector<std::string> dictionary;

    void cleanTrie(Node *curr) {
        if (curr == nullptr) return;
        for (Node *child : curr->children) {
            cleanTrie(child);
        }
        delete curr;
    }

public:
    AhoTrie() : root{new Node()} { }

    ~AhoTrie() { cleanTrie(root); }

    void addWord(const std::string &s) {
        Node *curr = root;
        for (char c : s) {
            if (curr->children[c-'a'] == nullptr) {
                curr->children[c-'a'] = new Node();
            }
            curr = curr->children[c-'a'];
        }
        curr->outputIndex = static_cast<int>(dictionary.size());
        dictionary.push_back(s);
    }

    void computeFailures() {
        root->failure = root;
        std::queue<Node *> q;
        for (Node *node : root->children) if (node != nullptr) { q.push(node); node->failure = root; }

        while (!q.empty()) {
            Node *curr = q.front(); q.pop();

            for (int i = 0; i < 26; ++i) if (curr->children[i] != nullptr) {
                Node *tmp = curr->failure;
                while (tmp->children[i] == nullptr && tmp != root) {
                    tmp = tmp->failure;
                }

                if (tmp->children[i] == nullptr) {
                    curr->children[i]->failure = root;
                } else {
                    curr->children[i]->failure = tmp->children[i];
                }

                q.push(curr->children[i]);
            }

            if (curr->failure->outputIndex >= 0) {
                curr->output = curr->failure;
            } else {
                curr->output = curr->failure->output;
            }
        }
    }

    std::vector<std::vector<int>> search(std::string &text) {
        Node *curr = root;
        std::vector<std::vector<int>> matches(static_cast<int>(dictionary.size()));

        for (int i = 0; i < static_cast<int>(text.size()); ++i) {
            char c = text[i];
            if (curr->children[c-'a'] == nullptr) {
                while (curr != root && curr->children[c-'a'] == nullptr) {
                    curr = curr->failure;
                }

                if (curr->children[c-'a'] != nullptr) { --i; }
            } else {
                curr = curr->children[c-'a'];
                if (curr->outputIndex >= 0) {
                    matches[curr->outputIndex].push_back(i);
                }

                Node *tmp = curr->output;
                while (tmp != nullptr) {
                    matches[tmp->outputIndex].push_back(i);
                    tmp = tmp->output;
                }
            }
        }

        return matches;
    }

    void debug() {
        std::cout << "root " << root << std::endl;
        std::queue<std::pair<char, Node *>> q;
        for (int i = 0; i < 26; ++i) if (root->children[i] != nullptr) { q.push({i+'a', root->children[i]}); }

        while (!q.empty()) {
            int lvl = static_cast<int>(q.size());

            for (int x = 0; x < lvl; ++x) {
                std::pair<char, Node *> curr = q.front(); q.pop();
                if (curr.second == nullptr) {
                    std::cout << " | ";
                    continue;
                } else {
                    std::cout << "(" << curr.first << "," << curr.second << "<" << curr.second->failure << "," << curr.second->output << "," << curr.second->outputIndex << ">) ";
                    bool added = false;
                    for (int i = 0; i < 26; ++i) if (curr.second->children[i] != nullptr) {
                        q.push({i+'a', curr.second->children[i]});
                        added = true;
                    }
                    if (added)
                        q.push({' ', nullptr});
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::vector<std::string> dictionary = { "p", "pup" };

    AhoTrie t;
    for (std::string &s : dictionary) {
        t.addWord(s);
    }

    t.computeFailures();

    t.debug();

    std::string text = "popup";
    std::vector<std::vector<int>> matches = t.search(text);
    for (int i = 0; i < static_cast<int>(matches.size()); ++i) {
        std::cout << dictionary[i] << ":";
        for (int ind : matches[i]) {
            std::cout << ' ' << ind;
        }
        std::cout << std::endl;
    }

    return 0;
}
