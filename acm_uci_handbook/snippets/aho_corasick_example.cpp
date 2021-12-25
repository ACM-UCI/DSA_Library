void aho_example(const std::string &search, const std::vector<std::string> &patterns) {
    Aho aho(patterns);
    Aho::AhoAutomata automata = aho.getAutomata();

    for (int i = 0; i < (int) search.length(); ++i) {
        automata.next(search[i]);
        for (const int &id : automata) {
            std::cout <<
                patterns[id] << " terminates at index " << i << std::endl;
        }
    }

    return 0;
}
