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

struct SqStack {
    int *base;
    int *top;
    int size;
};

Status Init(SqStack &s) {
    s.base = (int*) malloc (MAX_STACK_SIZE * sizeof(int));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}

Status Push(SqStack &s, int elem) {
    if(s.top - s.base >= s.size) {
        s.base = (int*) realloc (s.base, s.size * 2 * sizeof(int));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size = s.size * 2;
    }
    s.top++;
    *(s.top) = elem;
    return OK;
}

bool IsEmpty(SqStack s) {
    return s.base == s.top;
}

Status Pop(SqStack &s, int &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    s.top--;
    return OK;
}

Status Top(SqStack s, int &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    return OK;
}

int main() {

    SqStack stack1;
    Init(stack1);
    Push(stack1, 1);
    int tmp;
    Top(stack1, tmp);
    cout << tmp << '\n';
    Pop(stack1, tmp);
    cout << tmp << '\n';
    Push(stack1, 2);
    Top(stack1, tmp);
    cout << tmp << '\n';

}