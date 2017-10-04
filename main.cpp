#include <iostream>
#include <fstream>
#include <string>

#include "parse.h"
#include "nfa.h"

#define INPUT "input.txt"
#define OUTPUT "2016_11076.out"

using namespace std;

int T;

const char* test_regexp(string, string);

int main() {
    ifstream fin(INPUT);
    ofstream fout(OUTPUT);

    // Test cases
    fin >> T;

    while (T--) {
        string dummy, reg, in;
        fin >> dummy >> reg >> in;
        fout << test_regexp(reg, in) << endl;
    }

    return 0;
}

// function that tests whether the input matches to rexp
const char* test_regexp(string reg, string in) {
    string postfix = to_postfix(reg);
    NFA* nfa = construct_nfa(postfix);
    if (nfa->match(in)) {
        return "yes";
    } else {
        return "no";
    }
}
