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
typedef int ElemType;

#define LIST_INIT_SIZE 256;

struct SqList {
    int *elem;
    int length;
    int size;
};

Status InitList(SqList &L) {
    L.elem = (ElemType*) malloc ()
}