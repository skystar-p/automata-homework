#include "nfa.h"
#include "state.h"
#include <string>
#include <stack>

using namespace std;

// convert char to enum class Char
Char char_to_Char(char c) {
    if (c == '0') return Char::Zero;
    else if (c == '1') return Char::One;
    // actually not happen, but for consistency
    else return Char::Null;
}

// various constructors for convinience
NFA::NFA(char c) : NFA(char_to_Char(c)) {}

NFA::NFA(Char c) {
    State* b = new State(false);
    State* e = new State(true);
    b->add_transition(c, e);
    begin = b;
    end = e;
}

NFA::NFA(State* begin, State* end): begin(begin), end(end) {}

// for clean final state mark
void NFA::clear_final() {
    begin->make_not_final();
    end->make_not_final();
}

// "." concatenation operator
NFA* nfa_concat(NFA* a, NFA* b) {
    // first clean final mark
    a->clear_final();
    b->clear_final();
    // draw an arrow from end of a to begin of b
    a->end->add_transition(Char::Null, b->begin);
    // and mark end of b with final state
    b->end->make_final();
    return new NFA(a->begin, b->end);
}

NFA* nfa_union(NFA* a, NFA* b) {
    // clean final marks
    a->clear_final();
    b->clear_final();
    // generate new states
    State* new_begin = new State(false);
    State* new_end = new State(true);

    // branches to two from new_begin, and merged later into new_end
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

    // just draw some arrows
    new_begin->add_transition(Char::Null, a->begin);
    a->end->add_transition(Char::Null, new_end);
    a->end->add_transition(Char::Null, a->begin);
    new_begin->add_transition(Char::Null, new_end);
    return new NFA(new_begin, new_end);
}

// match function
bool NFA::match(string target) {
    set<State*> current_states;
    // initialize current states with initial state(begin)
    current_states = begin->get_same_state();
    for (auto x: target) {
        Char c = char_to_Char(x);
        set<State*> new_states;
        // get one char, takes transition, and stores at new_states
        new_states = get_transition_state(c, current_states);
        // ... and update it with transition of new_states (with empty string)
        current_states = get_same_state(new_states);
    }

    for (auto s: current_states) {
        // if some states is final state, return true
        if (s->is_final()) {
            return true;
        }
    }
    return false;
}

NFA* construct_nfa(string postfix) {
    stack<NFA*> nfa_stack;
    for (auto c: postfix) {
        // if '0' or '1', just call constructor with it
        if (c == '0' || c == '1') {
            nfa_stack.push(new NFA(c));
        }
        // union
        else if (c == '+') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            NFA* s = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(nfa_union(f, s));
        }
        // concat
        else if (c == '.') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            NFA* s = nfa_stack.top();
            nfa_stack.pop();
            // order is reversed (because it is stack)
            nfa_stack.push(nfa_concat(s, f));
        }
        // asterisk
        else if (c == '*') {
            NFA* f = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(nfa_asterisk(f));
        }
    }
    // finally remaining one is the result of constructed NFA
    return nfa_stack.top();
}
