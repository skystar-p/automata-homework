#include <string>
#include <unordered_map>
#include <vector>
#include "turing.h"

using namespace std;

Turing::Turing(string input_string) {
    // insert sharps in front and back
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
    // run while machine gets into halt state
    while (!current_state->is_final) {
        char current_head = tape[head];
        Transition* trans = current_state->transitions[current_head];

        tape[head] = trans->write;
        head += trans->direction;

        // if tape direction is S (stop), halt immediately
        if (trans->direction == 0) {
            break;
        }

        // if go right at the back, increase the tape size
        if ((unsigned) head == tape.size()) {
            tape.push_back('#');
        }

        // update the current state
        current_state = trans->end;
        current_state_name = trans->end->name;
    }
}
