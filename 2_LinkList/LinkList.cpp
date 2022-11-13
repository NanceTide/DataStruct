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
    int data;
    LinkNode *next;
};
typedef LinkNode *LinkList;

Status Init(LinkList &head) {
    head = (LinkList) malloc (sizeof(LinkNode));
    head->data = 0;
    head->next = nullptr;
    return OK;
}

Status RearInsert(LinkList &head, int elem) {
    LinkList p = head;
    while(p->next)
        p = p->next;
    LinkList newTmp = (LinkList) malloc (sizeof(LinkNode));
    p->next = newTmp;
    newTmp->data = elem;
    newTmp->next = nullptr;
    return OK;
}

Status HeadInsert(LinkList &head, int elem) {
    LinkList newTmp = (LinkList) malloc (sizeof(LinkNode));
    newTmp->data = elem;
    LinkList tmp = head->next;
    newTmp->next = tmp;
    head->next = newTmp;
    return OK;
}

Status RearInsert(LinkList &head, int elem, int index) {
    if(index < 0)
        return ERROR;
    LinkList p = head;
    for(int i = 0; i < index; i++) {
        if(!p->next)
            return ERROR;
        p = p->next;
    }
    LinkList newTmp = (LinkList) malloc (sizeof(LinkNode));
    newTmp->data = elem;
    LinkList tmp = p->next;
    p->next = newTmp;
    newTmp->next = tmp;
    return OK;
}

Status HeadInsert(LinkList &head, int elem, int index) {
    if(index <= 0)
        return ERROR;
    LinkList p = head;
    for(int i = 0; i < index - 1; i++) {
        if(!p->next)
            return ERROR;
        p = p->next;
    }
    LinkList newTmp = (LinkList) malloc (sizeof(LinkNode));
    newTmp->data = elem;
    LinkList tmp = p->next;
    newTmp->next = tmp;
    p->next = newTmp;
    return OK;
}

bool IsEmpty(LinkList head) {
    if(head->next)
        return false;
    else
        return true;
}

int Length(LinkList head) {
    LinkList p = head;
    int i = 0;
    while(p->next) {
        i++;
        p = p->next;
    } 
    return i;
}

int Find(LinkList head, int elem) {
    if(IsEmpty(head))
        return 0;
    LinkList p = head;
    int i = 0;
    while(p->next) {
        p = p->next;
        i++;
        if(p->data == elem)
            return i;
    }
    return 0;
}

Status Prt(LinkList head) {
    LinkList p = head; // head空时仍然有效
    while(p->next) {
        p = p->next;
        cout << p->data << '\n';
    }
    return OK;
}

Status Get(LinkList head, int &elem, int index) {
    LinkList p = head;
    for(int i = 0; i < index; i++) {
        p = p->next;
        if(!p)
            return ERROR;
    }
    elem = p->data;
    return OK;
}

Status Reverse(LinkList &head) {
    if(IsEmpty(head)) // head空时 p无效
        return OK;
    LinkList p = head->next->next;
    LinkList tmp;
    head->next->next = nullptr; // 无效化第一个有效项的指针，否则最后会形成环
    while(p) {
        tmp = p->next;
        p->next = head->next;
        head->next = p;
        p = tmp;
    }
    return OK;
}

LinkList Reverse_2(LinkList head) {
    LinkNode *prev, *curr;
    prev = head->next;
    head->next = nullptr;
    while(prev) {
        curr = prev;
        prev = prev->next;
        curr->next = head->next;
        head->next = curr;
    }
    return head;
}

LinkList GetMiddleLeft(LinkList head) {
    LinkList fast = head;
    LinkList slow = head;
    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow; 
}

int main() {
    LinkList a;
    Init(a);
    HeadInsert(a, 4);
    RearInsert(a, 9);
    HeadInsert(a, 3);
    HeadInsert(a, 1);
    cout << GetMiddleLeft(a)->data << '\n';
    Prt(a);

}