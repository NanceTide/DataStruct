#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;

typedef struct LinkNode {
    int data;
    LinkNode *next;
}*LinkList;

Status InitList(LinkList &head) {
    head = (LinkList) malloc (sizeof(LinkNode));
    head->data = 0;
    head->next = nullptr;
    if(!head)
        exit(OVERFLOW);
    return OK;
}

Status DestroyList(LinkList &head) {
    
}