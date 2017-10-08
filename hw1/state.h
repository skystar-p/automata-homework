#ifndef STATE_H
#define STATE_H
#include <vector>
#include <set>

using namespace std;

// enum for distinguish 0, 1, and empty string
enum class Char {
    Zero,
    One,
    Null
};

class State {
    public:
        State(bool is_final);
        bool is_final();
        void make_final();
        void make_not_final();
        void add_transition(Char, State*);
        set<State*> get_same_state();
        set<State*> get_transition_state(Char);
        vector<pair<Char, State*>> transitions;
    private:
        bool final_state;
};

set<State*> get_same_state(set<State*>);
set<State*> get_transition_state(Char, set<State*>);
#endif
