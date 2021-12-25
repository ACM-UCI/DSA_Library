// s is the search string, p is the pattern string set
void aho_example(const std::string &s, const std::vector<std::string> &p) {
    Aho aho(p);
    Aho::AhoAutomata automata = aho.getAutomata();

    for (int i = 0; i < (int) s.length(); ++i) {
        automata.next(s[i]);
        for (const int &id : automata) {
            std::cout << p[id] << " terminates at index " << i << std::endl;
        }
    }

    return 0;
}
