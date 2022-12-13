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

#define LIST_INIT_SIZE 256

struct SqList {
    ElemType *elem;
    int length;
    int size;
};

Status InitList(SqList &L) {
    L.elem = new ElemType[LIST_INIT_SIZE];
    if(!L.elem)
        return ERROR;
    L.length = 0;
    L.size = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert(SqList &L, ElemType elem, int index = 0) {
    if(L.length + 1 >= L.size)
        exit(OVERFLOW);
    if(index < 0 || index > L.length)
        return ERROR;
    for(int i = L.length - 1; i > index; i--)
        L.elem[i + 1] = L.elem[i];
    L.elem[index] = elem;
    L.length++;
    return OK;
}

Status ListReverse(SqList &L) {
    if(L.length == 0)
        return OK;
    for(int i = 0, j = L.length - 1; i < j; i++, j--) {
        int t = 0;
        t = L.elem[i];
        L.elem[i] = L.elem[j];
        L.elem[j] = t;
    }
    return OK;
}

Status ListPrint(SqList &L) {
    for(int i = 0; i < L.length; i++)
        cout << L.elem[i] << ' ';
    cout << '\n';
    return OK;
}

int main() {
    SqList list;
    InitList(list);
    for(int i = 0; i < 10; i++)
        ListInsert(list, i, i);
    ListPrint(list);
    ListReverse(list);
    ListPrint(list);
    return 0;

}