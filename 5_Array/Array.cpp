#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_DIM_SIZE 8
typedef int Status;

struct Array {
    int *base;
    int dim;
    int *bounds;
    int *constants;
};

Status InitArray(Array &A, int dim, ...) {
    va_list ap;
    va_start(ap, dim);

    if(dim <= 0 || dim > MAX_DIM_SIZE)
        return ERROR;
    A.dim = dim;
    A.bounds = (int*) malloc (sizeof(int) * dim);
    int elemtotal = 1;
    for(int i = 0; i < dim; i++) {
        A.bounds[i] = va_arg(ap, int);
        elemtotal *= A.bounds[i];
    }
    va_end(ap);

    A.base = (int*) malloc (sizeof(int) * elemtotal);
    A.constants = (int*) malloc (sizeof(int) * dim);
    if(!A.base || !A.constants || !A.bounds)
        return OVERFLOW;

    A.constants[dim - 1] = 1;
    for(int i = dim - 2; i >= 0; i--)
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1];

    return OK;
}

Status DestrotArray(Array &A) {
    free(A.base);
    free(A.bounds);
    free(A.constants);
    A.base = nullptr;
    A.bounds = nullptr;
    A.constants = nullptr;
    A.dim = 0;
    return OK;
}

Status Locate(Array A, va_list ap, int &off) {
    off = 0;
    for(int i = 0, ind = 0; i < A.dim; i++) {
        ind = va_arg(ap, int);
        if(ind < 0 || ind >= A.bounds[i])
            return OVERFLOW;
        off += ind * A.constants[i];
    }

    va_end(ap);
    return OK;
}

Status Assign(Array &A, int elem, ...) {
    va_list ap;
    va_start(ap, elem);
    int off;

    int result = Locate(A, ap, off);
    if(result == OVERFLOW)
        return OVERFLOW;

    *(A.base + off) = elem;
    return OK;
}

Status Value(Array A, int &elem, ...) {
    va_list ap;
    va_start(ap, elem);
    int off;

    int result = Locate(A, ap, off);
    if(result == OVERFLOW)
        return OVERFLOW;

    elem = *(A.base + off);
    return OK;
}

int main() {
    Array a;

    InitArray(a, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8 * 7 * 6 * 5; i++)
        a.base[i] = i * 10;

    int elem = 100;
    cout << Value(a, elem, 1, 1, 1, 7) << '\n';
    cout << elem;
    return 0;

}