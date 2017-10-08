#include "state.h"
#include <vector>
#include <set>

using namespace std;

State::State(bool is_final) {
    final_state = is_final;
}

bool State::is_final() {
    return final_state;
}

void State::make_final() {
    final_state = true;
}

void State::make_not_final() {
    final_state = false;
}

// follow the empty string direction, and return all corresponding states
set<State*> State::get_same_state() {
    set<State*> state_set;
    // self is same state with self
    state_set.insert(this);
    for (auto p: transitions) {
        // if transition is empty string
        if (p.first == Char::Null) {
            // insert it
            state_set.insert(p.second);
            set<State*> rest_set;
            // ... and insert others recursively
            rest_set = p.second->get_same_state();
            // merge two sets
            state_set.insert(rest_set.begin(), rest_set.end());
        }
    }
    return state_set;
}

// bulk set operation for fetching same states
set<State*> get_same_state(set<State*> group_set) {
    set<State*> state_set;
    for (auto p: group_set) {
        set<State*> rest_set;
        rest_set = p->get_same_state();
        state_set.insert(rest_set.begin(), rest_set.end());
    }
    return state_set;
}

// look for transition state
set<State*> State::get_transition_state(Char c) {
    set<State*> state_set;
    for (auto p: transitions) {
        // if transition corresponds,
        if (p.first == c) {
            // insert it
            state_set.insert(p.second);
        }
    }
    return state_set;
}

// bulk set operation for fetching same trasition states
set<State*> get_transition_state(Char c, set<State*> group_set) {
    set<State*> state_set;
    for (auto p: group_set) {
        set<State*> rest_set;
        rest_set = p->get_transition_state(c);
        state_set.insert(rest_set.begin(), rest_set.end());
    }
    return state_set;
}

// add transition arrow
void State::add_transition(Char c, State* next) {
    transitions.push_back(make_pair(c, next));
}
