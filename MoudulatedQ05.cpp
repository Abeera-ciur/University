#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string stack[500];
int top = -1;

void pushTOstack(string value) {
    top++;
    stack[top] = value;
}

string popFROMstack() {
    string value = stack[top];
    top--;
    return value;
}

bool isOperand(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    return 1;
}

string removeSpaces(string text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] != ' ') {
            result += text[i];
        }
    }
    return result;
}

bool hasOnlyValidCharacters(string expr) {
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if (!isOperand(c) && !isOperator(c) && c != '(' && c != ')') {
            return false;
        }
    }
    return true;
}

bool isValidInfix(string expr) {
    int brackets = 0;
    bool expectOperand = true;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isOperand(c)) {
            if (!expectOperand) return false;
            expectOperand = false;
        }
        else if (c == '(') {
            if (!expectOperand) return false;
            brackets++;
        }
        else if (c == ')') {
            if (expectOperand) return false;
            brackets--;
            if (brackets < 0) return false;
        }
        else {
            if (expectOperand) return false;
            expectOperand = true;
        }
    }

    return brackets == 0 && !expectOperand;
}

string makeExpression(string left, char op, string right, int outputType) {
    if (outputType == 1) return "(" + left + op + right + ")";
    if (outputType == 2) return left + right + op;
    return op + left + right;
}

string infixToPostfix(string expr, bool forPrefix) {
    top = -1;
    string result = "";

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isOperand(c)) {
            result += c;
        }
        else if (c == '(') {
            pushTOstack("(");
        }
        else if (c == ')') {
            while (stack[top] != "(") {
                result += popFROMstack();
            }
            popFROMstack();
        }
        else {
            while (top != -1 && stack[top] != "(") {
                int topPrec = precedence(stack[top][0]);
                int currentPrec = precedence(c);
                bool shouldPop = false;

                if (topPrec > currentPrec) {
                    shouldPop = true;
                }
                else if (topPrec == currentPrec) {
                    if (forPrefix && c == '^') shouldPop = true;
                    if (!forPrefix && c != '^') shouldPop = true;
                }

                if (!shouldPop) break;
                result += popFROMstack();
            }
            pushTOstack(string(1, c));
        }
    }

    while (top != -1) {
        result += popFROMstack();
    }
    return result;
}

string infixToPrefix(string expr) {
    reverse(expr.begin(), expr.end());

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }

    string result = infixToPostfix(expr, true);
    reverse(result.begin(), result.end());
    return result;
}

// outputType: 1 = infix, 2 = postfix, 3 = prefix
// returns "" if the expression is invalid
string convertPostfixOrPrefix(string expr, bool inputIsPrefix, int outputType) {
    top = -1;

    if (inputIsPrefix) {
        reverse(expr.begin(), expr.end());
    }

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (isOperand(c)) {
            pushTOstack(string(1, c));
        }
        else if (isOperator(c)) {
            if (top < 1) return "";

            string first = popFROMstack();
            string second = popFROMstack();
            string left, right;

            if (inputIsPrefix) {
                left = first;
                right = second;
            } else {
                left = second;
                right = first;
            }

            pushTOstack(makeExpression(left, c, right, outputType));
        }
        else {
            return "";
        }
    }

    if (top != 0) return "";
    return stack[0];
}

void showMenu() {
    cout << endl;
    cout << "1. Infix to Postfix" << endl;
    cout << "2. Infix to Prefix" << endl;
    cout << "3. Postfix to Infix" << endl;
    cout << "4. Prefix to Infix" << endl;
    cout << "5. Prefix to Postfix" << endl;
    cout << "6. Postfix to Prefix" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice." << endl;
            continue;
        }
        if (choice == 0) break;
        if (choice < 1 || choice > 6) {
            cout << "Invalid choice." << endl;
            continue;
        }

        string expr;
        cout << "Enter your expression: ";
        cin.ignore(1000, '\n');
        getline(cin, expr);
        expr = removeSpaces(expr);

        if (expr == "") {
            cout << "Expression is empty." << endl;
            continue;
        }
        if (expr.length() >= 500) {
            cout << "Expression is too long." << endl;
            continue;
        }
        if (!hasOnlyValidCharacters(expr)) {
            cout << "Expression has invalid characters." << endl;
            continue;
        }

        string result;

        if (choice == 1 || choice == 2) {
            if (!isValidInfix(expr)) {
                cout << "Invalid infix expression." << endl;
                continue;
            }
            if (choice == 1) {
                cout << "Postfix expression: " << infixToPostfix(expr, false) << endl;
            } else {
                cout << "Prefix expression: " << infixToPrefix(expr) << endl;
            }
        }
        else {
            if (choice == 3) result = convertPostfixOrPrefix(expr, false, 1);
            if (choice == 4) result = convertPostfixOrPrefix(expr, true, 1);
            if (choice == 5) result = convertPostfixOrPrefix(expr, true, 2);
            if (choice == 6) result = convertPostfixOrPrefix(expr, false, 3);

            if (result == "") {
                cout << "Invalid expression." << endl;
            }
            else if (choice == 3 || choice == 4) {
                cout << "Infix expression: " << result << endl;
            }
            else if (choice == 5) {
                cout << "Postfix expression: " << result << endl;
            }
            else {
                cout << "Prefix expression: " << result << endl;
            }
        }
    }
    return 0;
}