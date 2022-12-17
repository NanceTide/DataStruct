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

template <typename ElemType> struct SqStack {
    ElemType *base;
    ElemType *top;
    int size;
};

template <typename ElemType> Status Init(SqStack<ElemType> &s) {
    s.base = (ElemType*) malloc (MAX_STACK_SIZE * sizeof(ElemType));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}

template <typename ElemType> Status IsEmpty(SqStack<ElemType> s) {
    return s.base == s.top;
}

template <typename ElemType> Status Push(SqStack<ElemType> &s, ElemType elem) {
    if(s.top - s.base >= s.size) {
        s.base = (ElemType*) realloc (s.base, s.size * 2 * sizeof(ElemType));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size *= 2;
    }
    s.top++;
    *(s.top) = elem;
    return OK;
}

template <typename ElemType> Status Pop(SqStack<ElemType> &s, ElemType &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    s.top--;
    return OK;
}

template <typename ElemType> Status Top(SqStack<ElemType> s, ElemType &elem) {
    if(IsEmpty(s))
        return ERROR;
    elem = *(s.top);
    return OK;
}

template <typename ElemType> struct SqQueue {
    ElemType *base;
    int front;
    int rear;
};

template <typename ElemType> Status Init(SqQueue<ElemType> &q) {
    q.base = (ElemType*) malloc (MAX_SQ_SIZE * sizeof(ElemType));
    if(!q.base)
        return OVERFLOW;
    q.front = 0;
    q.rear = 0;
    return OK;
}

template <typename ElemType> Status IsEmpty(SqQueue<ElemType> q) {
    return q.front == q.rear;
}

template <typename ElemType> Status IsFull(SqQueue<ElemType> q) {
    return (q.rear + 1) % MAX_SQ_SIZE == q.front;
}

template <typename ElemType> Status Push(SqQueue<ElemType> &q, ElemType elem) {
    if(IsFull(q))
        return ERROR;
    q.base[q.rear] = elem;
    q.rear = (q.rear + 1) % MAX_SQ_SIZE;
    return OK;
}

template <typename ElemType> Status Pop(SqQueue<ElemType> &q, ElemType &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    q.front = (q.front + 1) % MAX_SQ_SIZE;
    return OK;
}

template <typename ElemType> Status Top(SqQueue<ElemType> q, ElemType &elem) {
    if(IsEmpty(q))
        return ERROR;
    elem = q.base[q.front];
    return OK;
}

Status PreOrderTraverse_(BiTree root, Status (*Visit)(int elem)) {
    if(!root)
        return OK;
    SqStack<BiTree> s;
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
    SqStack<BiTree> s;
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
    SqStack<BiTree> s, ans;
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
    SqQueue<BiTree> q;
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

Status SwapLeftRight(BiTree root) {
    if(!root)
        return OK;
    BiTree tmp;
    tmp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = tmp;
    return OK;
}

bool IsSimilarTree(BiTree root0, BiTree root1) {
    if(!root0 && !root1)
        return true;
    else if(!root0 || !root1)
        return false;
    return IsSimilarTree(root0->lchild, root1->lchild) && IsSimilarTree(root0->rchild, root1->rchild);
}

bool IsCompleteTree(BiTree root) {
    if(!root)
        return true;
    else {
        SqQueue<BiTree> root_queue;
        Init(root_queue);
        Push(root_queue, root);
        while(!IsEmpty(root_queue)) {
            BiTree curr;
            Pop(root_queue, curr);
            if(!curr)
                break;
            else {
                if(curr->lchild)
                    Push(root_queue, curr->lchild);
                if(curr->rchild)
                    Push(root_queue, curr->rchild);
            }
        }

        while(!IsEmpty(root_queue)){
            BiTree curr;
            Pop(root_queue, curr);
            if(curr)
                return false;
        }
    }    
    return true;   

}


int main() {

    BiTree root0, root1;
    PreOrderCreate(root0);
    
    auto prt = [](int val) -> Status {
        printf("%d ", val);
        return OK;
    };

    PreOrderTraverse(root0, prt);
    cout << '\n';
    PreOrderTraverse_(root0, prt);
    cout << '\n';
    InOrderTraverse(root0, prt);
    cout << '\n';
    InOrderTraverse_(root0, prt);
    cout << '\n';
    PostOrderTraverse(root0, prt);
    cout << '\n';
    PostOrderTraverse_(root0, prt);
    cout << '\n';
    LevelOrderTraverse(root0, prt);
    cout << '\n';
    cout << "深度：" << Depth(root0);
    cout << '\n';
    cout << "叶子结点个数：" << LeafCount(root0);
    cout << '\n';
    cout << "结点个数：" << NodeCount(root0);
    cout << '\n';
    cout << "是否为完全二叉树：" << IsCompleteTree(root0);
    cout << '\n';
    cout << "左右互换后：";
    SwapLeftRight(root0);
    PreOrderTraverse(root0, prt);
    cout << '\n';

    return 0;

}