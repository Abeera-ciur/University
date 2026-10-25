// Ques 6. Give code for the following conversions using Stack data structure. The program should
// display a menu allowing the user to select the desired conversion type. Based on the selected
// option, the program should prompt the user to enter an expression in the appropriate format (Infix,
// Prefix, or Postfix), perform the conversion using a stack, and display the resulting expression.
// Infix to postfix
// • Infix to prefix
// • Postfix to Infix
// • Prefix to Infix
// • Prefix to Postfix
// • Postfix to Prefix 





#include<iostream>
#include<string>
using namespace std;

char stack[500];
int top = -1;

void infixTOprefix();
void postfixTOinfix();
void prefixTOinfox();
void prefixTOpostfix();
void postfixTOprefix();
void infixTOpostfix();
void pushTOstack(int value, int precedence);
void popFROMstack();
void checkStacknCOmpare(int PINP);


int main(){

    
    infixTOprefix();
    


    return 0;
}

void pushTOstack(int value, int precedence){
    if(top==499){
        cout<<"Stack Full, Kindly try with another expression."<<endl; //just in case check
        return;
    }

    int stackTOPprecedence = precedence;
    stack[++top]= value;

}
void popFROMstack(){
    if(top==-1){
        cout<<"Stack Empty, Kindly try with an expression."<<endl; //just in case check
        return;
    }

    //precedence = ^ */ +-
    cout<<stack[top--];

}

void checkStacknCOmpare(int PINP, char opt){ //opt as operator is a keyword

    if(opt == '('){
        pushTOstack(opt, 0); return;
    }
    if(stack[top]<PINP){
        pushTOstack(opt, PINP); return;
    }
    if (stack[top]>PINP){
        popFROMstack();
        pushTOstack(opt, PINP); return;
    }


    return;
    
}

void infixTOprefix(){
 // A*(B+C)/D-E  TO -/*A+BCDE

    string expression;
    cout<<"Enter your expression: ";
    cin>>expression;


    if(expression.length()==499){
        cout<<"Expression is too long. Kindly try a different one."<<endl;
        return;
    }

    for(char character : expression){
        if(character>='A' && character<='Z' || character>='a' && character<='z'){
            cout<<character;
        }
        if(character =='('){
            checkStacknCOmpare(0, '(');
        }
        if(character =='+'){
            checkStacknCOmpare(1, '+');
        }
        if(character =='-'){
            checkStacknCOmpare(1, '-');
        }
        if(character =='/'){
            checkStacknCOmpare(2, '/');
        }
        if(character =='*'){
            checkStacknCOmpare(2, '*');
        }
        if(character =='^'){
            checkStacknCOmpare(3, '^');
        }
        if(character == ')'){
            do{ popFROMstack();}
            while(character !='(');
            popFROMstack();
        }
        
        


        return;
    }
    do{popFROMstack();}while(top !=-1);
}



void postfixTOinfix(){


    return;
}
void prefixTOinfox(){


    return;
}
void prefixTOpostfix(){


    return;
}
void postfixTOprefix(){


    return;
}
void infixTOpostfix(){


    return;
}