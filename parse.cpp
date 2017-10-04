#include <string>
#include <stack>

using namespace std;

string to_postfix(string& k) {
    stack<char> operator_stack;
    string res = "";
    for (unsigned i = 0; i < k.size(); i++) {
        char c = k[i];
        switch (c) {
            case '(':
                operator_stack.push(c);
                break;
            case ')':
                while (true) {
                    char curr = operator_stack.top();
                    operator_stack.pop();
                    if (curr == '(') {
                        break;
                    }
                    else {
                        res += curr;
                    }
                }
                break;
            case '0':
            case '1':
                res += c;
                break;
            default:
                operator_stack.push(c);
        }
    }
    return res;
}
