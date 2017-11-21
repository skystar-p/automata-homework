#include <string>
#include <vector>
#include "state.h"

using namespace std;

Transition::Transition(char input_, char pop_, string push_, State* next_) {
    input = input_;
    pop = pop_;
    push = push_;
    next = next_;
}

State::State() {
    is_final = false;
}

void State::add_trans(char input_, char pop_, string push_, State* next_) {
    transitions.push_back(new Transition(input_, pop_, push_, next_));
}

void State::make_final() {
    is_final = true;
}
