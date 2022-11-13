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

struct BiNode {
    int val;
    BiNode *lchild, *rchild;
};
typedef BiNode *BiTree;

typedef BiTree Elemtype;

Status PreOrderCreate(BiTree &root) {
    int num;
    scanf("%d", &num);
    if(num == -1)
        root = nullptr;
    else {
        root = (BiTree) malloc (sizeof(BiNode));
        if(!root)
            exit(OVERFLOW);
        root->val = num;
        PreOrderCreate(root->lchild);
        PreOrderCreate(root->rchild);
    }
    return OK;
}

Status PreOrderTraverse(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    if(Visit(root->val))
        if(PreOrderTraverse(root->lchild, Visit))
            if(PreOrderTraverse(root->rchild, Visit))
                return OK;
    return ERROR;
}

Status InOrderTraverse(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    if(InOrderTraverse(root->lchild, Visit))
        if(Visit(root->val))
            if(InOrderTraverse(root->rchild, Visit))
                return OK;
    return ERROR;
}

Status PostOrderTraverse(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    if(PostOrderTraverse(root->lchild, Visit))
        if(InOrderTraverse(root->rchild, Visit))
            if(Visit(root->val))
                return OK;
    return ERROR;
}

#pragma region // 栈定义

struct SqStack {
    Elemtype *base;
    Elemtype *top;
    int size;
};

Status Init(SqStack &s) {
    s.base = (Elemtype*) malloc (MAX_STACK_SIZE * sizeof(Elemtype));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}

Status IsEmpty(SqStack s) {
    return s.base == s.top;
}

Status Push(SqStack &s, Elemtype elem) {
    if(s.top - s.base >= s.size) {
        s.base = (Elemtype*) realloc (s.base, s.size * 2 * sizeof(Elemtype));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size *= 2;
    }
    s.top++;
    *(s.top) = elem;
    return OK;
}

Status Pop(SqStack &s, Elemtype &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    s.top--;
    return OK;
}

Status Top(SqStack s, Elemtype &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    return OK;
}

#pragma endregion

#pragma region // 队列定义

struct SqQueue {
    Elemtype *base;
    int front;
    int rear;
};

Status Init(SqQueue &q) {
    q.base = (Elemtype*) malloc (MAX_SQ_SIZE * sizeof(Elemtype));
    if(!q.base)
        return OVERFLOW;
    q.front = 0;
    q.rear = 0;
    return OK;
}

Status IsEmpty(SqQueue q) {
    return q.front == q.rear;
}

Status IsFull(SqQueue q) {
    return (q.rear + 1) % MAX_SQ_SIZE == q.front;
}

Status Push(SqQueue &q, Elemtype elem) {
    if(IsFull(q))
        return ERROR;
    q.base[q.rear] = elem;
    q.rear = (q.rear + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Pop(SqQueue &q, Elemtype &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    q.front = (q.front + 1) % MAX_SQ_SIZE;
    return OK;
}

Status Top(SqQueue q, Elemtype &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    return OK;
}

#pragma endregion

Status PreOrderTraverse_(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    SqStack s;
    Init(s);
    Push(s, root);
    BiTree curr;
    while(!IsEmpty(s)) {
        Pop(s, curr);
        if(!Visit(curr->val))
            return ERROR;
        if(curr->rchild)
            Push(s, curr->rchild);
        if(curr->lchild)
            Push(s, curr->lchild);
    }
    return OK;
}

Status InOrderTraverse_(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    SqStack s;
    Init(s);
    BiTree curr = root;
    while(curr || !IsEmpty(s)) {
        if(curr) {
            Push(s, curr);
            curr = curr->lchild;
        } else {
            Pop(s, curr);
            if(!Visit(curr->val))
                return ERROR;
            curr = curr->rchild;
        }
    }
    return OK;
}

Status PostOrderTraverse_(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    SqStack s, ans;
    Init(s);
    Init(ans);
    Push(s, root);
    BiTree curr;
    while(!IsEmpty(s)) {
        Pop(s, curr);
        Push(ans, curr);
        if(curr->lchild)
            Push(s, curr->lchild);
        if(curr->rchild)
            Push(s, curr->rchild);
    }
    while(!IsEmpty(ans)) {
        Pop(ans, curr);
        if(!Visit(curr->val))
            return ERROR;
    }
    return OK;
}

Status LevelOrderTraverse(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return ERROR;
    SqQueue q;
    Init(q);
    BiTree curr = root;
    Push(q, curr);
    while(!IsEmpty(q)) {
        Pop(q, curr);
        if(!Visit(curr->val))
            return ERROR;
        if(curr->lchild)
            Push(q, curr->lchild);
        if(curr->rchild)
            Push(q, curr->rchild);
    }
    return OK;
}

Status Copy(BiTree root, BiTree &nroot) {
    if(!root) {
        nroot = nullptr;
        return OK;
    }
    nroot = (BiTree) malloc (sizeof(BiNode));
    if(!nroot)
        return ERROR;
    nroot->val = root->val;
    if(Copy(root->lchild, nroot->lchild))
        if(Copy(root->rchild, nroot->rchild))
            return OK;
    return ERROR;
}

int Depth(BiTree root) {
    if(!root)
        return 0;
    int m = Depth(root->lchild);
    int n = Depth(root->rchild);
    return m > n ? m + 1 : n + 1; 
}

int NodeCount(BiTree root) {
    if(!root)
        return 0;
    return NodeCount(root->lchild) + NodeCount(root->rchild) + 1;
}

int LeafCount(BiTree root) {
    if(!root)
        return 0;
    if(!root->lchild && !root->rchild)
        return 1;
    return LeafCount(root->lchild) + LeafCount(root->rchild);
}

int main() {

    BiTree T0, T1;
    auto prt = [](int elem) -> Status {
        printf("%d ", elem);
        return OK;
    };

    PreOrderCreate(T0);

    PreOrderTraverse(T0, prt);

    cout << '\n' << Depth(T0) << '\n' << NodeCount(T0) << '\n' << LeafCount(T0);

    // PreOrderTraverse(T0, prt);
    // printf("\n");
    // PreOrderTraverse_(T0, prt);
    // printf("\n");
    // InOrderTraverse(T0, prt);
    // printf("\n");
    // InOrderTraverse_(T1, prt);
    // printf("\n");
    // PostOrderTraverse(T0, prt);
    // printf("\n");
    // PostOrderTraverse_(T0, prt);
    // printf("\n");
    // LevelOrderTraverse(T0, prt);
    
    return 0;

}