#include <string>
#include <stack>

using namespace std;

// convert infix to postfix
string to_postfix(string& k) {
    stack<char> operator_stack;
    string res = "";
    for (unsigned i = 0; i < k.size(); i++) {
        char c = k[i];
        // look each token and do some operations
        switch (c) {
            case '(':
                operator_stack.push(c);
                break;
            case ')':
                // pop operator while meet corresponding left parenthesis, and append operator
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
                // just append to result
                res += c;
                break;
            default:
                // the rest of options are operator
                operator_stack.push(c);
        }
    }
    return res;
}
