#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


string stack[500];
int top = -1;
int prefixFLAG = false;


void infixTOprefix();
void postfixTOinfix();
void prefixTOinfox();
void prefixTOpostfix();
void postfixTOprefix();
void infixTOpostfix();
void pushTOstack(string value, int precedence);
string popFROMstack();
void checkStacknCOmpare(int PINP, char opt, string &result);


int main() {


    int choice;
    bool running = true;


    while (running) {


        cout << "\n===== Expression Conversion Menu =====" << endl;
        cout << "1. Infix to Postfix" << endl;
        cout << "2. Infix to Prefix" << endl;
        cout << "3. Postfix to Infix" << endl;
        cout << "4. Prefix to Infix" << endl;
        cout << "5. Prefix to Postfix" << endl;
        cout << "6. Postfix to Prefix" << endl;
        cout << "7. Exit" << endl;


        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {


            case 1:
                infixTOpostfix(); break;


            case 2:
                infixTOprefix(); break;


            case 3:
                postfixTOinfix(); break;


            case 4:
                prefixTOinfox(); break;


            case 5:
                prefixTOpostfix(); break;


            case 6:
                postfixTOprefix(); break;


            case 7:
                running = false;
                cout << "Program ended." << endl;
                break;


            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }


    return 0;
}


void pushTOstack(string value, int precedence) {


    if (top == 499) {
        cout << "Stack Full, kindly try another expression." << endl;
        return;
    }


    stack[++top] = value;
}


string popFROMstack() {


    if (top == -1) {
        return "";
    }
    return stack[top--];
}


void checkStacknCOmpare(int PINP, char opt, string &result) {


    if (opt == '(') {
        pushTOstack("(", 0);
        return;
    }


    if (top == -1 || stack[top] == "(") {
        pushTOstack(string(1, opt), PINP);
        return;
    }


    int stackTOPprecedence;


    if (stack[top] == "^")
        stackTOPprecedence = 3;
    else if (stack[top] == "*" || stack[top] == "/")
        stackTOPprecedence = 2;
    else
        stackTOPprecedence = 1;


    if (prefixFLAG) {


        if (stackTOPprecedence < PINP ||
            (opt != '^' && stackTOPprecedence == PINP)) {
            pushTOstack(string(1, opt), PINP);
        }
        else {
            result += stack[top--];
            checkStacknCOmpare(PINP, opt, result);
        }


    }
    else {


        if (stackTOPprecedence < PINP ||
            (opt == '^' && stackTOPprecedence == PINP)) {


            pushTOstack(string(1, opt), PINP);
        }
        else {
            result += stack[top--];
            checkStacknCOmpare(PINP, opt, result);
        }


    }
}




void infixTOprefix() {


    top = -1;
    prefixFLAG = true;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        prefixFLAG = false;
        return;
    }


    reverse(expression.begin(), expression.end());


    for (int i = 0; i < expression.length(); i++) {


        if (expression[i] == '(')
            expression[i] = ')';
        else if (expression[i] == ')')
            expression[i] = '(';


    }


    string result = "";


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            result += character;
        }
        else if (character == '(') {


            pushTOstack("(", 0);
        }
        else if (character == ')') {


            while (top != -1 && stack[top] != "(") {
                result += popFROMstack();
            }


            if (top != -1)
                popFROMstack();
        }
        else if (character == '+' || character == '-') {


            checkStacknCOmpare(1, character, result);
        }
        else if (character == '*' || character == '/') {


            checkStacknCOmpare(2, character, result);
        }
        else if (character == '^') {


            checkStacknCOmpare(3, character, result);
        }


    }


    while (top != -1) {
        result += popFROMstack();
    }


    reverse(result.begin(), result.end());


    prefixFLAG = false;


    cout << "Prefix expression: " << result << endl;
}


void postfixTOinfix() {


    top = -1;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        return;
    }


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            pushTOstack(string(1, character), 0);
        }
        else if (character == '+' || character == '-' ||
                 character == '*' || character == '/' ||
                 character == '^') {


            string right = popFROMstack();
            string left = popFROMstack();


            string result = "(" + left + character + right + ")";


            pushTOstack(result, 0);
        }


    }


    if (top == 0) {
        cout << "Infix expression: " << stack[top] << endl;
    }
    else {
        cout << "Invalid postfix expression." << endl;
    }
}


void prefixTOinfox() {


    top = -1;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        return;
    }


    reverse(expression.begin(), expression.end());


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            pushTOstack(string(1, character), 0);
        }
        else if (character == '+' || character == '-' ||
                 character == '*' || character == '/' ||
                 character == '^') {


            string left = popFROMstack();
            string right = popFROMstack();


            string result = "(" + left + character + right + ")";


            pushTOstack(result, 0);
        }


    }


    if (top == 0) {
        cout << "Infix expression: " << stack[top] << endl;
    }
    else {
        cout << "Invalid prefix expression." << endl;
    }
}


void prefixTOpostfix() {


    top = -1;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        return;
    }


    reverse(expression.begin(), expression.end());


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            pushTOstack(string(1, character), 0);
        }
        else if (character == '+' || character == '-' ||
                 character == '*' || character == '/' ||
                 character == '^') {


            string left = popFROMstack();
            string right = popFROMstack();


            string result = left + right + character;


            pushTOstack(result, 0);
        }


    }


    if (top == 0) {
        cout << "Postfix expression: " << stack[top] << endl;
    }
    else {
        cout << "Invalid prefix expression." << endl;
    }
}


void postfixTOprefix() {


    top = -1;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        return;
    }


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            pushTOstack(string(1, character), 0);
        }
        else if (character == '+' || character == '-' ||
                 character == '*' || character == '/' ||
                 character == '^') {


            string right = popFROMstack();
            string left = popFROMstack();


            string result = character + left + right;


            pushTOstack(result, 0);
        }


    }


    if (top == 0) {
        cout << "Prefix expression: " << stack[top] << endl;
    }
    else {
        cout << "Invalid postfix expression." << endl;
    }
}


void infixTOpostfix() {


    top = -1;
    prefixFLAG = false;


    string expression;


    cout << "Enter your expression: ";
    cin >> expression;


    if (expression.length() >= 500) {
        cout << "Expression is too long." << endl;
        return;
    }


    string result = "";


    for (char character : expression) {


        if ((character >= 'A' && character <= 'Z') ||
            (character >= 'a' && character <= 'z') ||
            (character >= '0' && character <= '9')) {


            result += character;
        }
        else if (character == '(') {


            pushTOstack("(", 0);
        }
        else if (character == ')') {


            while (top != -1 && stack[top] != "(") {
                result += popFROMstack();
            }


            if (top != -1)
                popFROMstack();
        }
        else if (character == '+' || character == '-') {


            checkStacknCOmpare(1, character, result);
        }
        else if (character == '*' || character == '/') {


            checkStacknCOmpare(2, character, result);
        }
        else if (character == '^') {


            checkStacknCOmpare(3, character, result);
        }


    }


    while (top != -1) {
        result += popFROMstack();
    }


    cout << "Postfix expression: " << result << endl;


}
