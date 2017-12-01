#include <iostream>
#include <fstream>
#include "state.h"
#include "turing.h"

using namespace std;

void build_turing(string);

Turing* turing;

int main(int argc, char** argv) {
    if (argc < 2) return 0;
    string filename (argv[1]);

    string input_string;
    cin >> input_string;

    turing = new Turing(input_string);

    build_turing(filename);

    turing->run();

    cout << turing->count() << endl;

    return 0;
}

void build_turing(string filename) {
    ifstream fin(filename);
    int state_count, transition_count;
    fin >> state_count >> transition_count;

    for (int i = 0; i < state_count; i++) {
        string name;
        int is_final;
        fin >> name >> is_final;

        turing->add_state(new State(name, (bool)is_final));

        if (i == 0) {
            turing->current_state = turing->states[name];
            turing->current_state_name = name;
        }
    }

    for (int i = 0; i < transition_count; i++) {
        string start, end;
        char read, write;
        int direction;

        fin >> start >> end >> read >> write >> direction;

        turing->states[start]->add_transition(
                turing->states[start],
                turing->states[end],
                read,
                write,
                direction
        );
    }
}
