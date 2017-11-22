#include <string>
#include <vector>
#include "dpa.h"

#include <iostream>

using namespace std;

// list of acceptable characters
char chars[] = {
    'a', 'b', 'c', 'd', 'x', 'y', 'z', '2', '3', '4', '5', '6', '7'
};

// list of accepatble operators
char opers[] = {
    '+', '-', '*', '/', '(', ')'
};

// constructor for DPA class
DPA::DPA(State* start_, State* end_) {
    start = start_;
    end = end_;
}

// function for building dpa state transition map.
// accept language that is provided in homework pdf
DPA* build_dpa() {
    State* start = new State();
    State* q = new State();
    State* q_plus = new State();
    State* q_minus = new State();
    State* q_mul = new State();
    State* q_div = new State();
    State* q_lpar = new State();
    State* q_rpar = new State();
    State* q_sharp = new State();
    State* done = new State();

    // from initial state to q
    start->add_trans('e', '#', "E#", q);

    // id
    for (char c: chars) {
        State* q_id = new State();
        q->add_trans(c, 'e', "", q_id);

        q_id->add_trans('e', 'E', "TG", q_id);
        q_id->add_trans('e', 'T', "FU", q_id);
        q_id->add_trans('e', 'F', "A", q_id);
        q_id->add_trans('e', 'A', string(1, c), q_id);

        q_id->add_trans('e', c, "", q);
    }

    // plus
    q->add_trans('+', 'e', "", q_plus);

    q_plus->add_trans('e', 'G', "+TG", q_plus);
    q_plus->add_trans('e', 'U', "", q_plus);

    q_plus->add_trans('e', '+', "", q);

    // minus
    q->add_trans('-', 'e', "", q_minus);

    q_minus->add_trans('e', 'G', "-TG", q_minus);
    q_minus->add_trans('e', 'U', "", q_minus);

    q_minus->add_trans('e', '-', "", q);

    // mul
    q->add_trans('*', 'e', "", q_mul);

    q_mul->add_trans('e', 'U', "*FU", q_mul);

    q_mul->add_trans('e', '*', "", q);

    // div
    q->add_trans('/', 'e', "", q_div);

    q_div->add_trans('e', 'U', "/FU", q_div);

    q_div->add_trans('e', '/', "", q);

    // lpar
    q->add_trans('(', 'e', "", q_lpar);

    q_lpar->add_trans('e', 'E', "TG", q_lpar);
    q_lpar->add_trans('e', 'T', "FU", q_lpar);
    q_lpar->add_trans('e', 'F', "(E)", q_lpar);

    q_lpar->add_trans('e', '(', "", q);

    // rpar
    q->add_trans(')', 'e', "", q_rpar);

    q_rpar->add_trans('e', 'G', "", q_rpar);
    q_rpar->add_trans('e', 'U', "", q_rpar);

    q_rpar->add_trans('e', ')', "", q);

    // sharp
    q->add_trans('#', 'e', "", q_sharp);

    q_sharp->add_trans('e', 'G', "", q_sharp);
    q_sharp->add_trans('e', 'U', "", q_sharp);

    q_sharp->add_trans('e', '#', "#", done);

    // make `done` state to be final state
    done->make_final();

    return new DPA(start, done);
}

// function for check if `input_str` is accepted by dpa
bool DPA::check(string input_str) {
    vector<char> input (input_str.begin(), input_str.end());
    // initially start with sharp
    input.push_back('#');
    unsigned int cursor = 0;
    State* curr = start;
    vector<char> stack;

    // ... also the stack
    stack.push_back('#');

    while (true) {
        bool has_passed = false;

        // iterate over transitions
        for (Transition* trans: curr->transitions) {
            bool input_match =
                (trans->input == input[cursor]) ||
                (trans->input == 'e');
            bool pop_match =
                (trans->pop == stack.back()) ||
                (trans->pop == 'e');

            // if input and stack top is matched, take the transition
            if (input_match && pop_match) {
                if (trans->input != 'e') {
                    if (cursor < input.size()) {
                        cursor++;
                    }
                }

                // logic for recording string
                if (trans->pop != 'e') {
                    bool is_proper_char = false;
                    for (char c: chars) {
                        if (stack.back() == c) {
                            is_proper_char = true;
                        };
                    }

                    for (char c: opers) {
                        if (stack.back() == c) {
                            is_proper_char = true;
                        };
                    }

                    if (is_proper_char) {
                        current_parsed += stack.back();
                    }

                    // pop the stack
                    stack.pop_back();
                }

                // push the string into the stack (conversely)
                for (int i = trans->push.size() - 1; i >= 0; i--) {
                    stack.push_back(trans->push[i]);
                }
                curr = trans->next;
                has_passed = true;

                string t;

                for (char c: stack) {
                    if (c == '#') continue;
                    t = c + t;
                }

                string result = current_parsed + t;

                // record the result and store
                if (record.empty() || result != record.back()) {
                    record.push_back(result);
                }
                break;
            }
        }
        if (!has_passed) {
            return false;
        }

        // if the state is final state, return true
        if (curr->is_final) {
            return true;
        }
    }
    return false;
}
