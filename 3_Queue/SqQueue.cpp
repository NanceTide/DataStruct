#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_SQ_SIZE 32
typedef int Status;
 
struct SqQueue {
    int *base;
    int front;
    int rear;
};

Status Init(SqQueue &q) {
    q.base = (int*) malloc (MAX_SQ_SIZE * sizeof(int));
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

Status Push(SqQueue &q, int elem) {
    if(IsFull(q))
        return ERROR;
    q.base[q.rear] = elem;
    q.rear = (q.rear + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Pop(SqQueue &q, int &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    q.front = (q.front + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Top(SqQueue q, int &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    return OK;
}

int main() {
    
    SqQueue q;
    int num;
    Init(q);
    
    Push(q, 1);
    Push(q, 2);
    Push(q, 3);

    Pop(q, num);
    Top(q, num);
    cout << num;
    
    return 0;

}