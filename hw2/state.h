#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>

using namespace std;

class State;
class Transition;

// E, G, T, U, F, A
// a, b, c, d, x, y, z, 2, 3, 4, 5, 6, 7
// e for epsilon

class State {
    public:
        State();
        void make_final();
        void add_trans(char, char, string, State*);

        vector<Transition*> transitions;
        bool is_final;
};

class Transition {
    public:
        Transition(char, char, string, State*);
        char input;
        char pop;
        string push;
        State* next;
};

#endif
