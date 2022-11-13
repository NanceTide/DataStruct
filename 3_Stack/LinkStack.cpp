#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 32

typedef int Status;
struct LinkNode {
    int elem;
    LinkNode *next;
};
typedef LinkNode *LinkStack;

Status Init(LinkStack &S) {
    S = nullptr;
    return OK;
}

Status Push(LinkStack &S, int elem) {

}

bool IsEmpty(LinkStack S) {
    if(S)
        return false;
    return true;
}

Status Pop(LinkStack &S, int &elem) {
    if(IsEmpty(S))
        return ERROR;
    LinkStack tmp = S->next;
    S->next = S->next->next;
    elem = tmp->elem;
    free(tmp);
    return OK;
}

Status Top(LinkStack S, int &elem) {
    if(IsEmpty(S))
        return ERROR;
    elem = S->next->elem;
    return OK;
}


int main() {

}