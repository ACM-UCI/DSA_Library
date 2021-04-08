#include <vector>
#include <algorithm>
#include <iostream>

/**
 * Class for iterating all combinations in a vector.
 *
 * example:
 * Combination c(vector);
 * while (c.hasNext()) {
 *  print(c.next());
 * }
 */
template <typename T>
class Combinations {
private:
    enum class State { begin, running, end };

    std::vector<T> arr;
    std::vector<bool> inset;
    std::vector<T> nextComb;
    int R;
    State state;
    
    void fillComb() {
        int j = 0;
        for (int i = 0; i < inset.size(); ++i) if (inset[i]) { nextComb[j++] = arr[i]; } }

public:
    Combinations<T>(std::vector<T>& arr, int r)
    : arr{arr}, R{r}, inset{std::vector<bool>(arr.size())}, nextComb{std::vector<T>(r)}, state{State::begin}  {
	    std::fill(inset.begin()+std::max(0, (int)arr.size()-r), inset.end(), 1);
        fillComb();
    }

    std::vector<T>& curr() { return nextComb; }

    std::vector<T>& next() {
        switch (state) {
            case State::begin:
                state = (std::next_permutation(inset.begin(), inset.end())) ? State::running : State::end;
                break;
            case State::running:
                fillComb();
                state = (std::next_permutation(inset.begin(), inset.end())) ? State::running : State::end;
        }
        return nextComb;
    }

    bool hasNext() { return state != State::end; }
};
