#ifndef NFA_H
#define NFA_H
#include "state.h"
#include <string>

class NFA {
    public:
        NFA(char);
        NFA(Char);
        NFA(State*, State*);
        State* begin;
        State* end;
        void clear_final();
        bool match(std::string);
};

Char char_to_Char(char);
NFA* construct_nfa(string);

#endif
