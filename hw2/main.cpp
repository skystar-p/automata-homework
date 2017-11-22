#include <iostream>
#include <string>

#include "dpa.h"

using namespace std;

void print_record(DPA*);

int main() {
    DPA* dpa = build_dpa();

    string input;

    cin >> input;

    if (dpa->check(input)) {
        cout << "YES" << endl;
        print_record(dpa);
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}

// function for print the record of dpa
void print_record(DPA* dpa) {
    bool is_first = true;
    for (string s: dpa->record) {
        if (is_first) {
            cout << s << endl;
        }
        else {
            cout << "=> " << s << endl;
        }
        is_first = false;
    }
}
