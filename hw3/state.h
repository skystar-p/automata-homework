#ifndef STATE_H
#define STATE_H

#include <string>
#include <unordered_map>

using namespace std;

class State;
class Transition;

class State {
    public:
        State(string, bool);
        string name;
        bool is_final;
        void add_transition(State*, State*, char, char, int);
        unordered_map<char, Transition*> transitions;
};

class Transition {
    public:
        Transition(State*, State*, char, char, int);

        State* start;
        State* end;
        char read, write;
        int direction; // left=-1, right=1
};

#endif
