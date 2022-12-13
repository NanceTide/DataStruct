#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;

typedef struct LinkNode {
    ElemType data;
    LinkNode *next;
}*LinkList;

Status InitList(LinkList &head) {
    head = new LinkNode;
    head->data = 0;
    head->next = nullptr;
    if(!head)
        exit(OVERFLOW);
    return OK;
}

Status ListDeleteBetween(LinkList &head, ElemType left, ElemType right) {
    LinkList p = head;
    while(p->next && p->next->data <= left)
        p = p->next;
    if(p->next && p->next->data < right) {
        LinkList q = p->next;
        while(q && q->data < right) {
            p->next = q->next;
            delete q;
            q = p->next;
        }
    }
    return OK;
}

Status ListHeadInsert(LinkList &head, ElemType elem, int index = 0) {
    LinkList p = head;
    if(!head)
        return ERROR;
    for(int i = 0; i < index; i++) {
        p = p->next;
        if(!p->next)
            return ERROR;
    }
    LinkList q = new LinkNode;
    if(!q)
        return OVERFLOW;
    q->data = elem;
    q->next = p->next;
    p->next = q;
    return OK;
}

Status ListTraverse(LinkList &head) {
    if(!head)
        return ERROR;
    LinkList p = head->next;
    while(p->next) {
        cout << p->data << ' ';
        p = p->next;
    }
    return OK;
}

Status ListDelete(LinkList &head, int index = 0) {
    if(!head)
        return ERROR;
    LinkList p = head;
    for(int i = 0; i < index; i++) {
        if(!p->next)
            return ERROR;
        p = p->next;
    }
    LinkList q = p->next;
    p->next = q->next;
    delete q;
    return OK;
}

int main() {

    LinkList list;
    InitList(list);
    for(int i = 20; i; i--) {
        ListHeadInsert(list, i);
    }
    ListTraverse(list);
    cout << '\n';

    ListDeleteBetween(list, 4, 9);
    ListTraverse(list);
    cout << '\n';

    ListHeadInsert(list, 999, 4);
    ListTraverse(list);
    cout << '\n';

    ListDelete(list, 4);
    ListTraverse(list);

}