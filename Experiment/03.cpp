#include <stack>
#include <string>
#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_STACK_SIZE 32
typedef int Status;

template <typename ElemType> struct SqStack {
    ElemType *base;
    ElemType *top;
    int size;
};

template <typename ElemType> bool IsEmpty(SqStack<ElemType> s) {
    return s.base == s.top;
}

template <typename ElemType> ElemType StackTop(SqStack<ElemType> &s) {
    if(IsEmpty(s))
        exit(ERROR);
    return *(s.base);
}

char PriorityCmp(char a, char b) {
    if(a == '(' && b == ')' || a == '#' && b == '#')
        return '=';
    else if(((a == '+' || a == '-') && (b == '*' || b == '/')) || a == '(' || b == '(' || a == '#')
        return '<';
    else
        return '>';
}

double Operate(double a, char b, double c) {
    switch(b) {
        case '+':
            return a + c;
        case '*':
            return a * c;
        case '/':
            return a / c;
        case '-':
            return a - c;
    }
    return -1;
}

int main() {

    string expe;
    stack<double> opnd;
    stack<char> optr;
    cin >> expe;

    double numTmp = 0;
    double numL;
    double numR;
    char operTmp;
    expe = expe + "#";
    optr.push('#');

    for(int i = 0; !(expe[i] == '#' && optr.top() == '#'); ) {
        if(isdigit(expe[i])) {
            numTmp *= 10;
            numTmp += expe[i] - '0';
            i++;
        }
        else {
            if(numTmp) {
                opnd.push(numTmp);
                numTmp = 0;
            }
            operTmp = expe[i];
            switch(PriorityCmp(optr.top(), operTmp)) {
                case '<':
                    optr.push(operTmp);
                    i++;
                    break;
                case '>':
                    numR = opnd.top();
                    opnd.pop();
                    numL = opnd.top();
                    opnd.pop();
                    operTmp = optr.top();
                    optr.pop();
                    opnd.push(Operate(numL, operTmp, numR));
                    break;
                case '=':
                    optr.pop();
                    i++;
                    break;
            }
        }
    }

    cout << opnd.top();
    return 0;

}