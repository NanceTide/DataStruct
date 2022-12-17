# 顺序栈的实现

```cpp
template <typename ElemType> struct SqStack {
    ElemType *base;
    ElemType *top;
    int size;
};

```

## 初始化顺序栈

1. 使用 malloc 函数动态分配内存，创建顺序栈的数组。
2. 如果分配内存失败，则返回 OVERFLOW。
3. 将顺序栈的栈顶指针设置为数组的第一个元素的地址，并将栈的大小设置为分配的内存大小。

```cpp
template <typename ElemType> Status Init(SqStack<ElemType> &s) {
    s.base = (ElemType*) malloc (MAX_STACK_SIZE * sizeof(ElemType));
    if(!s.base)
        return OVERFLOW;
    s.top = s.base;
    s.size = MAX_STACK_SIZE;
    return OK;
}
```

## 入栈

1. 如果栈满，则使用 realloc 函数扩大栈的大小。
2. 将元素压入栈顶。
3. 将栈顶指针向后移动一位。

```cpp
template <typename ElemType> Status Push(SqStack<ElemType> &s, ElemType elem) {
    if(s.top - s.base >= s.size) {
        s.base = (ElemType*) realloc (s.base, s.size * 2 * sizeof(ElemType));
        if(!s.base)
            return OVERFLOW;
        s.top = s.base + s.size;
        s.size = s.size * 2;
    }
    *(s.top) = elem;
    s.top++;
    return OK;
}
```

## 判空

1. 如果栈顶指针等于栈底指针，则栈为空，返回 true。
2. 否则，栈不为空，返回 false。

```cpp
template <typename ElemType> bool IsEmpty(SqStack<ElemType> s) {
    return s.base == s.top;
}
```

## 出栈

1. 如果栈为空，返回 ERROR。
2. 将栈顶指针向前移动一位，并将栈顶元素赋值给 elem 变量。

```cpp
template <typename ElemType> Status Pop(SqStack<ElemType> &s, ElemType &elem) {
    if(IsEmpty(s))
        return ERROR;
    s.top--;
    elem = *(s.top);
    return OK;
}
```

## 获取栈顶元素

1. 返回栈顶指针前一位的元素。
2. 所有函数都使用了模板，以支持多种数据类型。

```cpp
template <typename ElemType> ElemType Top(SqStack<ElemType> s) {
    return *(s.top - 1);
}
```