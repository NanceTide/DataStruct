#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_STACK_SIZE 128
#define MAX_SQ_SIZE 128
typedef int Status;

typedef struct BiThrNode {
    int val;
    BiThrNode *lchild, *rchild;
    int ltag, rtag;
}*BiThrTree;

Status PreOrderCreate(BiThrTree &root) {
    int num;
    scanf("%d", &num);
    if(num == -1)
        root = nullptr;
    else {
        root = (BiThrTree) malloc (sizeof(BiThrNode));
        if(!root)
            exit(OVERFLOW);
        root->val = num;
        root->ltag = 0;
        root->rtag = 0;
        PreOrderCreate(root->lchild);
        PreOrderCreate(root->rchild);
    }
    return ERROR;
}

BiThrTree pre;
Status PreThreading(BiThrTree root) {
    if(!root)
        return OK;
    if(!root->lchild) {
        root->ltag = 1;
        root->lchild = pre;
    }
    if(pre && !pre->rchild) {
        pre->rtag = 1;
        pre->rchild = root;
    }
    pre = root;
    if(!root->ltag)
        PreThreading(root->lchild);
    if(!root->rtag)
        PreThreading(root->rchild);
    return OK;
}

Status PreOrderThreading(BiThrTree &nroot, BiThrTree root) {
    nroot = (BiThrTree) malloc (sizeof(BiThrNode));
    if(!nroot)
        exit(OVERFLOW);
    nroot->ltag = 0;
    nroot->rtag = 1;
    if(!root) {
        nroot->lchild = nroot;
        nroot->rchild = nroot;
        return OK;
    }
    nroot->lchild = root;
    pre = nroot;
    PreThreading(root);
    pre->rchild = nroot;
    pre->rtag = 1;
    nroot->rchild = pre;
    return OK;
}

Status PreOrderTraverse(BiThrTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    BiThrTree curr = root->lchild;
    while(curr != root) {
        while(!curr->ltag) {
            if(!Visit(curr->val))
                return ERROR;
            curr = curr->lchild;
        }
        if(!Visit(curr->val))
            return ERROR;
        curr = curr->rchild;
    }
    return OK;
}

Status InThreading(BiThrTree root) {
    if(!root)
        return OK;
    InThreading(root->lchild);
    if(!root->lchild) {
        root->ltag = 1;
        root->lchild = pre;
    }
    if(pre && !pre->rchild) {
        pre->rtag = 1;
        pre->rchild = root;
    }
    pre = root;
    InThreading(root->rchild);
    return OK;
}

Status InOrderThreading(BiThrTree &nroot, BiThrTree root) {
    nroot = (BiThrTree) malloc (sizeof(BiThrNode));
    if(!nroot)
        exit(OVERFLOW);
    nroot->ltag = 0;
    nroot->rtag = 1;
    if(!root) {
        nroot->rchild = nroot;
        nroot->lchild = nroot;
        return OK;
    }
    nroot->lchild = root;
    pre = nroot;
    InThreading(root);
    pre->rchild = nroot;
    pre->rtag = 1;
    nroot->rchild = pre;
    return OK;
}

Status InOrderTraverse(BiThrTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    BiThrTree curr = root->lchild;
    while(curr != root) {
        while(curr->ltag == 0) {
            curr = curr->lchild;
        }
        if(!Visit(curr->val))
            return ERROR;
        while(curr->rtag == 1 && curr->rchild != root) {
            curr = curr->rchild;
            if(!Visit(curr->val))
                return ERROR;
        }
        curr = curr->rchild;
    }
    return OK;
}

int main() {

    auto prt = [](int elem) -> Status {
        printf("%d ", elem);
        return OK;
    };
    BiThrTree T0;
    PreOrderCreate(T0);
    PreOrderThreading(T0, T0);
    PreOrderTraverse(T0, prt);
    return 0;
}