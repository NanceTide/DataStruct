# 数组的表示

## C 语言的可变参数库

在详细了解数组之前，我们先了解一下 C 语言的可变参数库 <stdarg.h>。  
stdarg.h 为函数提供了变参功能。它的使用必须按如下步骤进行。

1. 函数原型的形参必须以一个 int 类型的变量和省略号 ... 结束。
   - 传递给 parmN 的实参是省略号部分的参数数量，传递给省略号的是 parmN 个参数。
2. 在函数定义中创建一个 va_list 类型的变量。
   - 下面假定该变量名为 ap。
3. 调用宏 va_start(va_list, int)。
   - 该宏接受两个参数，第一个参数传入 ap，第二个参数传入 parmN。这个宏可以初始化 ap。
4. 调用宏 va_arg(va_list, type)。
   - 该宏接受两个参数，第一个参数传入 ap，第二个参数传入一个类型名。宏 va_arg 在第一次调用时返回变参列表的第一项，以此类推，在第 n 次调用时返回变参列表的第 n 项。
   - 传入函数的变参的参数类型与填入 va_arg 的第二项的宏参数类型必须相匹配。与函数不同，宏不会执行自动类型转换，例如，传入 10 而填入 double 类型很有可能出错。
5. 调用宏 va_end(va_list)。
   - 该宏接受参数 ap。它将完成清理工作，释放动态分配内存。

下面是一个举例用的求和函数。

```cpp
#include <stdarg.h> 

double sum(int num, ...) {
    va_list ap;
    va_start(ap, num);

    double ans = 0;
    for(int i = 0; i < num; i++)
        ans += va_arg(ap, double);
    va_end(ap);

    return ans;
}

```
## 数组的定义

```cpp
struct Array {
    int *base;
    int dim;
    int *bounds;
    int *constants;
};
```
base 是数组元素的基址，dim 是数组的维数，bounds 是数组的维界基址，constants 是数组映像函数常量基址。

考察高维数组存储位置的计算公式。由于存储单元是一维的结构，而数组是多维结构，因此需要一个多维向一维映射的规则。类 C 语言以行序作为主序，下面也将以行序作为主序。

例如，对于一个数组元素 arr[3][5]，设数组声明为 arr[10][20]。  
&(arr[3][5]) = &(arr[0][0]) + (3 * 20 + 5);  
对于 arr[3][5][7]，设数组声明 arr[10][20][30]。  
&(arr[3][5][7]) = &(arr[0][0][0]) + (3 * 30 * 20 + 5 * 30 + 7);  
更一般地说， $\&(arr[j_1]...[j_n])=\&(arr[0]...[0])+\sum^{n-1}_{i=1}(j_i\prod^{n}_{k=i+1}b_k)+j_n$ 。

在 Array 初始化时，需要存储每一维度最多有多少元素、或者说维界，并存放于 bounds 中；在多维数组寻址时，例如声明为 arr[a][b][c] 的 arr[i][j][k] 寻址，首先用 i 乘以所有比它低的维度的维界，即 i * b * c，再用 j 乘以比它低的维度的维界，即 j * c，最后加 k。由此可见，从某一维开始，之前所有维的维界乘积是需要经常调用的变量。我们将它们提前计算出来，并存放于 constants 中。  
在这里，声明为 arr[a][b][c] 的 arr[i][j][k],其 Array 的 bounds = {a, b, c}，constants = {b * c, c, 1}。

# 数组的实现

## 创建

函数首先要进行 stdarg 相关工作，参考上述文档，此处不再赘述。传入函数的参数顺序与声明时填入的参数顺序相同。例如，声明为 arr[a][b][c] 的数组应传入 InitArray(arr, 4, a, b, c)。  

首先判断维数 dim 是否超限。接着需要录入每一维的维界，同时记录数组的最大元素个数，以便 malloc 元素基址。函数随后判断 malloc 是否成功。最后，还需要维护 constants[]，且 $constants[i]=\prod^{n}_{k=i}bounds[i+1]$，即从 i + 1 维开始往后每一维的维界乘积，以便快速检索元素。

```cpp
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
```

## 定位

该函数接受一个 va_list，然后把 va_list 中的每一项取出，分别与 constants[i] 相乘，最后将结果传出。这样就取得了高维元素地址相对于基址的偏移量。

```cpp
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
```

## 指定

值得一提的是，elem 并非变参的数量。stdarg.h 的函数可能还有其他用法。

```cpp
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
```

## 取值

```cpp
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
```