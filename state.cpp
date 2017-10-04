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

set<State*> State::get_same_state() {
    set<State*> state_set;
    state_set.insert(this);
    for (auto p: transitions) {
        if (p.first == Char::Null) {
            state_set.insert(p.second);
            set<State*> rest_set;
            rest_set = p.second->get_same_state();
            state_set.insert(rest_set.begin(), rest_set.end());
        }
    }
    return state_set;
}

set<State*> get_same_state(set<State*> group_set) {
    set<State*> state_set;
    for (auto p: group_set) {
        set<State*> rest_set;
        rest_set = p->get_same_state();
        state_set.insert(rest_set.begin(), rest_set.end());
    }
    return state_set;
}

set<State*> State::get_transition_state(Char c) {
    set<State*> state_set;
    for (auto p: transitions) {
        if (p.first == c) {
            state_set.insert(p.second);
        }
    }
    return state_set;
}

set<State*> get_transition_state(Char c, set<State*> group_set) {
    set<State*> state_set;
    for (auto p: group_set) {
        set<State*> rest_set;
        rest_set = p->get_transition_state(c);
        state_set.insert(rest_set.begin(), rest_set.end());
    }
    return state_set;
}

void State::add_transition(Char c, State* next) {
    transitions.push_back(make_pair(c, next));
}
