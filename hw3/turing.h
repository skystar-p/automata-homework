#ifndef TURING_H
#define TURING_H

#include <string>
#include <unordered_map>
#include <vector>
#include "state.h"

using namespace std;

class Turing {
    public:
        Turing(string);
        vector<char> tape;
        int head;
        void add_state(State*);
        State* current_state;
        string current_state_name;

        void run();
        int count();

        unordered_map<string, State*> states;
};

#endif
