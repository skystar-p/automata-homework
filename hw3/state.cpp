#include <string>
#include <unordered_map>
#include "state.h"

using namespace std;

State::State(string name_, bool is_final_=false) {
    name = name_;
    is_final = is_final_;
}

Transition::Transition(State* start_, State* end_, char read_, char write_, int direction_) {
    start = start_;
    end = end_;
    read = read_;
    write = write_;
    direction = direction_;
}

void State::add_transition(State* start, State* end, char read, char write, int direction) {
    transitions[read] = new Transition(start, end, read, write, direction);
}
