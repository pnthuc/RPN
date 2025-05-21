#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

enum Operator { ADD, SUB, MUL, DIV };

int getOperatorCode(char op) {
    switch (op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        default: return -1;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(const string& expr, vector<pair<bool, long long>>& postfix) {
    stack<char> ops;
    long long num = 0;
    bool hasNum = false;

    for (char c : expr) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
            hasNum = true;
        } else {
            if (hasNum) {
                postfix.emplace_back(true, num);
                num = 0;
                hasNum = false;
            }
            if (isspace(c)) continue;
            if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    postfix.emplace_back(false, getOperatorCode(ops.top()));
                    ops.pop();
                }
                if (!ops.empty() && ops.top() == '(') ops.pop();
                else throw runtime_error("Invalid expression: mismatched parentheses");
            } else if (getOperatorCode(c) != -1) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c) && ops.top() != '(') {
                    postfix.emplace_back(false, getOperatorCode(ops.top()));
                    ops.pop();
                }
                ops.push(c);
            } else {
                throw runtime_error("Invalid character in expression");
            }
        }
    }
    if (hasNum) postfix.emplace_back(true, num);
    while (!ops.empty()) {
        if (ops.top() == '(') throw runtime_error("Invalid expression: mismatched parentheses");
        postfix.emplace_back(false, getOperatorCode(ops.top()));
        ops.pop();
    }
}

double evaluatePostfix(const vector<pair<bool, long long>>& postfix) {
    stack<double> values;
    for (const auto& token : postfix) {
        if (token.first) {
            values.push(token.second);
        } else {
            if (values.size() < 2) throw runtime_error("Invalid postfix expression");
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            switch (token.second) {
                case ADD: values.push(a + b); break;
                case SUB: values.push(a - b); break;
                case MUL: values.push(a * b); break;
                case DIV:
                    if (b == 0) throw runtime_error("Division by zero");
                    values.push(a / b);
                    break;
                default: throw runtime_error("Unknown operator");
            }
        }
    }
    if (values.size() != 1) throw runtime_error("Invalid postfix evaluation");
    return values.top();
}

void printPostfix(const vector<pair<bool, long long>>& postfix) {
    for (const auto& token : postfix) {
        if (token.first) {
            cout << token.second << ' ';
        } else {
            char op;
            switch (token.second) {
                case ADD: op = '+'; break;
                case SUB: op = '-'; break;
                case MUL: op = '*'; break;
                case DIV: op = '/'; break;
                default: op = '?';
            }
            cout << op << ' ';
        }
    }
    cout << endl;
}

int main() {
    vector<string> expressions = {
        "3+4*(2-1)/5",
        "12*(5+3)-4/2",
        "100/(2+3*4)-7",
        "(8+2*5)/(1+3*2-4)",
        "50-((2+3)*4-8)/2",
        "7*(6/(1+2))-5+8/2"
    };

    for (const auto& expr : expressions) {
        vector<pair<bool, long long>> postfix;
        try {
            infixToPostfix(expr, postfix);

            cout << "Infix: " << expr << endl;
            cout << "Postfix: ";
            printPostfix(postfix);

            cout << "Result: " << evaluatePostfix(postfix) << endl;
            cout << "-----------------------------" << endl;
        } catch (const exception& e) {
            cerr << "Error in expression '" << expr << "': " << e.what() << endl;
        }
    }
}
