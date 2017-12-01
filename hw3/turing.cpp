#include <string>
#include <unordered_map>
#include <vector>
#include "turing.h"

using namespace std;

Turing::Turing(string input_string) {
    tape.push_back('#');
    for (char c: input_string) {
        tape.push_back(c);
    }
    tape.push_back('#');

    head = 1;
}

void Turing::add_state(State* state) {
    states[state->name] = state;
}

int Turing::count() {
    int cnt = 0;
    for (char c: tape) {
        if (c == '1') cnt++;
    }
    return cnt;
}

void Turing::run() {
    while (!current_state->is_final) {
        char current_head = tape[head];
        Transition* trans = current_state->transitions[current_head];

        tape[head] = trans->write;
        head += trans->direction;

        if (trans->direction == 0) {
            break;
        }

        if ((unsigned) head == tape.size()) {
            tape.push_back('#');
        }

        current_state = trans->end;
        current_state_name = trans->end->name;
    }
}
