#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_SQ_SIZE 256
#define MAX_STACK_SIZE 256
typedef int Status;
typedef char ElemType;
 
struct SqQueue {
    ElemType *base;
    int front;
    int rear;
};

Status Init(SqQueue &q) {
    q.base = (ElemType*) malloc (MAX_SQ_SIZE * sizeof(ElemType));
    if(!q.base)
        return OVERFLOW;
    q.front = 0;
    q.rear = 0;
    return OK;
}

int Length(SqQueue q) {
    return (q.rear - q.front + MAX_SQ_SIZE) % MAX_SQ_SIZE; 
}

bool IsEmpty(SqQueue q) {
    return q.rear == q.front;
}

bool IsFull(SqQueue q) {
    return (q.rear + 1) % MAX_SQ_SIZE == q.front;
} 

Status Push(SqQueue &q, ElemType elem) {
    if(IsFull(q))
        return ERROR;
    q.base[q.rear] = elem;
    q.rear = (q.rear + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Pop(SqQueue &q, ElemType &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    q.front = (q.front + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Top(SqQueue q, ElemType &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    return OK;
}

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

bool IsBracketMatched(string expe) {
    SqStack bracket_stack;
    Init(bracket_stack);
    for(auto c : expe) {
        if(IsEmpty(bracket_stack) && (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}'))
            Push(bracket_stack, c);
        else {
            char tmp;
            Top(bracket_stack, tmp);
            if(c == ')') {
                if(tmp == '(')
                    Pop(bracket_stack, tmp);
                else
                    return false;
            } else if(c == '}') {
                if(tmp == '{')
                    Pop(bracket_stack, tmp);
                else
                    return false;
            } else if(c == ']') {
                if(tmp == '[')
                    Pop(bracket_stack, tmp);
                else
                    return false;
            } else if(c == '(' || c == '[' || c == '{'){
                Push(bracket_stack, c);
            }
        }
    }
    if(IsEmpty(bracket_stack))
        return true;
    else
        return false;
}

bool IsCentrosymmetric_Stack(string expe) {
    SqStack expe_stack;
    Init(expe_stack);
    for(int i = 0; i < (expe.length() + 1) / 2; i++) {
        Push(expe_stack, expe[i]);
    }

    char tmp;
    for(int i = expe.length() / 2; i < expe.length(); i++) {
        Pop(expe_stack, tmp);
        if(tmp != expe[i])
            return false;
    } 

    return true;
}

bool IsCentrosymmetric_Queue(string expe) {
    SqQueue expe_queue;
    Init(expe_queue);
    for(int i = 0; i < (expe.length() + 1) / 2; i++) {
        Push(expe_queue, expe[i]);
    }

    char tmp;
    for(int i = expe.length() - 1; i > expe.length() / 2; i--) {
        Pop(expe_queue, tmp);
        if(tmp != expe[i])
            return false;
    }
    return true;
}

int main() {
    
    string expe;
    cin >> expe;
    cout << boolalpha;
    cout << "括号匹配:" << IsBracketMatched(expe) << '\n';
    cout << "中心对称（栈检测）:" << IsCentrosymmetric_Stack(expe) << '\n';
    cout << "括号匹配（队列检测）:" << IsCentrosymmetric_Queue(expe) << '\n';
    
    return 0;

}