#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_STACK_SIZE 32
typedef int Status;

template <typename T> struct SqStack {
    T *base;
    T *top;
    int size;
};

template <typename T> Status Init(SqStack<T> &s) {
    s.base = (T*) malloc (MAX_STACK_SIZE * sizeof(T));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}

template <typename T> Status Push(SqStack<T> &s, T elem) {
    if(s.top - s.base >= s.size) {
        s.base = (T*) realloc (s.base, s.size * 2 * sizeof(T));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size = s.size * 2;
    }
    s.top++;
    *(s.top) = elem;
    return OK;
}

template <typename T> bool IsEmpty(SqStack<T> s) {
    return s.base == s.top;
}

template <typename T> Status Pop(SqStack<T> &s, T &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    s.top--;
    return OK;
}

template <typename T> T Top(SqStack<T> s) {
    return *(s.top);
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
    SqStack<double> opnd;
    SqStack<char> optr;
    cin >> expe;
    Init(opnd);
    Init(optr);

    double numTmp = 0;
    double numL;
    double numR;
    char operTmp;
    expe = expe + "#";
    Push(optr, '#');

    for(int i = 0; !(expe[i] == '#' && Top(optr) == '#'); ) {
        if(isdigit(expe[i])) {
            numTmp *= 10;
            numTmp += expe[i] - '0';
            i++;
        }
        else {
            if(numTmp) {
                Push(opnd, numTmp);
                numTmp = 0;
            }
            operTmp = expe[i];
            switch(PriorityCmp(Top(optr), operTmp)) {
                case '<':
                    Push(optr, operTmp);
                    i++;
                    break;
                case '>':
                    Pop(opnd, numR);
                    Pop(opnd, numL);
                    Pop(optr, operTmp);
                    Push(opnd, Operate(numL, operTmp, numR));
                    break;
                case '=':
                    Pop(optr, operTmp);
                    i++;
                    break;
            }
        }
    }

    cout << Top(opnd);
    return 0;

}