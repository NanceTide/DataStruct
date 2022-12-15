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
typedef int ElemType;

struct SqStack {
    ElemType *base;
    ElemType *top;
    int size;
};

Status Init(SqStack &s) {
    s.base = (ElemType*) malloc (MAX_STACK_SIZE * sizeof(ElemType));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}

Status Push(SqStack &s, ElemType elem) {
    if(s.top - s.base >= s.size) {
        s.base = (ElemType*) realloc (s.base, s.size * 2 * sizeof(ElemType));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size = s.size * 2;
    }
    *(s.top) = elem;
    s.top++;
    return OK;
}

bool IsEmpty(SqStack s) {
    return s.base == s.top;
}

Status Pop(SqStack &s, ElemType &elem) {
    if(IsEmpty(s))
        return ERROR;
    s.top--;
    elem = *(s.top);
    return OK;
}

Status Top(SqStack s, ElemType &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top - 1);
    return OK;
}

int main() {

    SqStack stack1;
    Init(stack1);
    Push(stack1, 1);
    int tmp;
    Top(stack1, tmp);
    cout << tmp << '\n';
    // Pop(stack1, tmp);
    // cout << tmp << '\n';
    Push(stack1, 2);
    Top(stack1, tmp);
    cout << tmp << '\n';

}