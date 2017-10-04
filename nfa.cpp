#include "nfa.h"
#include "state.h"
#include <string>
#include <stack>

using namespace std;

Char char_to_Char(char c) {
    if (c == '0') return Char::Zero;
    else if (c == '1') return Char::One;
    else return Char::Null;
}

NFA::NFA(char c) : NFA(char_to_Char(c)) {}

NFA::NFA(Char c) {
    State* b = new State(false);
    State* e = new State(true);
    b->add_transition(c, e);
    begin = b;
    end = e;
}

NFA::NFA(State* begin, State* end): begin(begin), end(end) {}

void NFA::clear_final() {
    begin->make_not_final();
    end->make_not_final();
}

NFA* nfa_concat(NFA* a, NFA* b) {
    a->clear_final();
    b->clear_final();
    a->end->add_transition(Char::Null, b->begin);
    b->end->make_final();
    return new NFA(a->begin, b->end);
}

NFA* nfa_union(NFA* a, NFA* b) {
    a->clear_final();
    b->clear_final();
    State* new_begin = new State(false);
    State* new_end = new State(true);

    new_begin->add_transition(Char::Null, a->begin);
    new_begin->add_transition(Char::Null, b->begin);
    a->end->add_transition(Char::Null, new_end);
    b->end->add_transition(Char::Null, new_end);
    return new NFA(new_begin, new_end);
}

NFA* nfa_asterisk(NFA* a) {
    a->clear_final();
    State* new_begin = new State(false);
    State* new_end = new State(true);

    new_begin->add_transition(Char::Null, a->begin);
    a->end->add_transition(Char::Null, new_end);
    a->end->add_transition(Char::Null, a->begin);
    new_begin->add_transition(Char::Null, new_end);
    return new NFA(new_begin, new_end);
}

bool NFA::match(string target) {
    set<State*> current_states;
    current_states = begin->get_same_state();
    for (auto x: target) {
        Char c = char_to_Char(x);
        set<State*> new_states;
        new_states = get_transition_state(c, current_states);
        current_states = get_same_state(new_states);
    }

    for (auto s: current_states) {
        if (s->is_final()) {
            return true;
        }
    }
    return false;
}

NFA* construct_nfa(string postfix) {
    stack<NFA*> nfa_stack;
    for (auto c: postfix) {
        if (c == '0' || c == '1') {
            nfa_stack.push(new NFA(c));
        }
        else if (c == '+') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            NFA* s = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(nfa_union(f, s));
        }
        else if (c == '.') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            NFA* s = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(nfa_concat(s, f));
        }
        else if (c == '*') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(nfa_asterisk(f));
        }
    }
    return nfa_stack.top();
}
