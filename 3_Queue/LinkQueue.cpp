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
#define MAX_SQ_SIZE 8
typedef int Status;

typedef struct QueueNode {
    int data;
    QueueNode *next;
}QueueNode, *QueuePtr;
struct LinkQueue {
    QueuePtr front;
    QueuePtr rear;
};
 
Status Init(LinkQueue &q) {
    q.front = (QueuePtr) malloc (sizeof(QueueNode));
    q.rear = q.front;
    q.front->next = nullptr;
    return OK;
}

Status Push(LinkQueue &q, int elem) {
    QueuePtr tmp = (QueuePtr) malloc (sizeof(QueueNode));
    tmp->data = elem;
    tmp->next = nullptr;
    q.rear->next = tmp;
    q.rear = tmp;
    return OK;
}

Status Pull(LinkQueue &q, int &elem) {
    if(q.rear == q.front)
        return ERROR;
    QueuePtr tmp = q.front->next;
    q.front->next = tmp->next;
    elem = tmp->data;
    free(tmp);
    return OK;
}

Status Top(LinkQueue q, int &elem) {
    if(q.rear == q.front)
        return ERROR;
    elem = q.front->next->data;
    return OK;
}

Status Prt(LinkQueue q) {
    QueuePtr tmp;
    tmp = q.front;
    while(tmp->next) {
        tmp = tmp->next;
        cout << tmp->data << '\n';
    }
    return OK;
}

int main() {
    LinkQueue q;
    Init(q);
    Push(q, 1);
    Push(q, 2);
    Push(q, 3);
    int num;
    Prt(q);
    Top(q, num);
    cout << num;
    return 0;
}