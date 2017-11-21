#ifndef DPA_H
#define DPA_H

#include <string>
#include <vector>
#include "state.h"

using namespace std;

class DPA {
    public:
        DPA(State*, State*);
        bool check(string);

        State* start;
        State* end;

        vector<string> record;
        string current_parsed;
};

DPA* build_dpa();

#endif
