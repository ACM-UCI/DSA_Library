/*
 *        _                                     _      _    
 *   __ _| |__   ___     ___ ___  _ __ __ _ ___(_) ___| | __
 *  / _` | '_ \ / _ \   / __/ _ \| '__/ _` / __| |/ __| |/ /
 * | (_| | | | | (_) | | (_| (_) | | | (_| \__ \ | (__|   < 
 *  \__,_|_| |_|\___/   \___\___/|_|  \__,_|___/_|\___|_|\_\
 *                                                          
 *
 */

#include <algorithm>

#include <vector>
#include <array>
#include <queue>
#include <string>

class Aho {
private:
    struct Node {
        Node *suffix;   // pointer to longest prefix that is a suffix of this node
        Node *output;   // pointer to longest word that is a suffix of this node
        std::vector<int> wordids;   // ids of all words terminated at this node (allows for duplicate words in dictionary
        std::array<Node *, 256> c;  // links to children of node

        Node() : suffix{nullptr}, output{nullptr}, wordids{std::vector<int>()} {
            std::fill(std::begin(c), std::end(c), nullptr);
        }
    };

private:
    Node *root;

public:
    class AhoAutomata {
    private:
        Aho::Node *root;
        Aho::Node *curr;
    public:
        AhoAutomata(Aho::Node *root) : root{root}, curr{root} { }

        // Advances the AhoAutomata to the next character, follows suffix link on failure
        void next(char c) {
            Aho::Node *tmp = curr;
            while (tmp->c[c] == nullptr && tmp != root) { tmp = tmp->suffix; }
            if (tmp->c[c] != nullptr) { curr = tmp->c[c]; }
            else { curr = root; }
        }


        class Iterator {
        private:
            Node *outputnode;
            int index;
        public:
            Iterator(Node *outputnode) : outputnode{outputnode}, index{0} {
                if (this->outputnode != nullptr && this->outputnode->wordids.empty()) { this->outputnode = outputnode->output; }
            }

            int operator*() { return outputnode->wordids[index]; }
            Iterator &operator++() {
                if (outputnode != nullptr) {
                    if (++index >= static_cast<int>(outputnode->wordids.size())) {
                        outputnode = outputnode->output;
                        index = 0;
                    }
                }
                return *this;
            }

            bool operator==(const Iterator &other) { return outputnode == other.outputnode && index == other.index; }
            bool operator!=(const Iterator &other) { return outputnode != other.outputnode || index != other.index; }
        };

        AhoAutomata::Iterator begin() { return AhoAutomata::Iterator(curr); }
        AhoAutomata::Iterator end() { return AhoAutomata::Iterator(nullptr); }
    };

private:
    // Perform BFS to construct suffix and output links
    void computeLinks() {
        root->suffix = root;            // suffix link of root is itself

        std::queue<Node *> q;
        for (Node *next : root->c) if (next != nullptr) {
            next->suffix = root;        // direct decendents of root have suffix link pointing to root
            q.push(next);
        }

        while (!q.empty()) {
            Node *curr = q.front(); q.pop(); // curr will already have its suffix link built, we will build for children
            for (int c = 0; c < 256; ++c) if (curr->c[c] != nullptr) {
                Node *suffixofcurr = curr->suffix;  // a proper suffix of curr which will be checked to find a proper suffix of curr->c[c]
                while (suffixofcurr->c[c] == nullptr && suffixofcurr != root) { suffixofcurr = suffixofcurr->suffix; }
                if (suffixofcurr->c[c] != nullptr) { curr->c[c]->suffix = suffixofcurr->c[c]; }
                else { curr->c[c]->suffix = root; }
                q.push(curr->c[c]);
            }
            if (!(curr->suffix->wordids.empty())) { curr->output = curr->suffix; }
            else { curr->output = curr->suffix->output; }
        }
    }

public:
    Aho(const std::vector<std::string> &dict) : root{new Node()} {
        for (int i = 0; i < static_cast<int>(dict.size()); ++i) {
            Node *curr = root;
            for (const char &c : dict[i]) {
                if (curr->c[c] == nullptr) { curr->c[c] = new Node(); }
                curr = curr->c[c];
            }
            curr->wordids.push_back(i);
        }

        computeLinks();
    }

    ~Aho() {
        std::queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            Node *curr = q.front(); q.pop();
            for (int c = 0; c < 256; ++c) if (curr->c[c] != nullptr) {
                q.push(curr->c[c]);
            }
            delete curr;
        }
    }

    AhoAutomata getAutomata() { return AhoAutomata(root); }

};
