# 顺序队列的表示

## 顺序队列的定义

顺序队列是一种先进先出(First In First Out, FIFO)的操作受限线性表。队列只能在表的一端进行插入，在另一端进行删除。

在我们的实现中，base 表示分给队列的空间的起始位置。front 和 rear 是两个整型，base + front 指向队列尾部的元素，即出队的那一方向；base + rear 指向队列头部的元素，即入队的那一方向。

如果是下面提及的第三种情况，则 base + rear 指向队列头部的下一个元素，当队列不满时，这始终是一个空元素。

```cpp
struct SqQueue {
    Elemtype *base;
    int front;
    int rear;
};
```

## 循环队列相关

由于顺序队列只在头部插入、尾部删除，有时会在存储区未满时发生溢出。称这种情况为假溢出。

循环队列的使用能够避免假溢出情况的出现。具体的实现方法是无论插入或删除，一旦 rear 或 front 自增时超出了所分配的队列空间，就让它指向这片连续空间的起始位置。这样能最大化利用存储区的空间。

但在循环队列中，当队列为空或队列为满时，都有 front == rear。可以作如下改动之一以区分这两种情况。

- 另设一个 emptyFlag 来指示队列是否为空。
- 另设一个 length 来指示队列的元素个数。
- 在队列中只使用 MAX_SQ_SIZE - 1 个空间。rear 始终指向最新入队元素的下一个元素。
    - 当队列空时，front 与 rear 重合，有 front == rear。
    - 每当 front 或 rear 自增时，有 pointer = (pointer + 1) % MAX_SQ_SIZE。
    - 当队列满时，front 与 rear + 1 重合，有 (rear + 1) % MAX_SQ_SIZE == front。

# 顺序队列的实现

下列算法都默认使用循环队列的第三种情况。

## 初始化

```cpp
Status Init(SqQueue &q) {
    q.base = (int*) malloc (MAX_SQ_SIZE * sizeof(int));
    if(!q.base)
        return OVERFLOW;
    q.front = 0;
    q.rear = 0;
    return OK;
}
```

## 判空

```cpp
bool IsEmpty(SqQueue q) {
    return q.rear == q.front;
}
```

## 判满

当队列满时，front 与 rear + 1 重合。并不清楚 rear + 1 是否越界，因此必须对 MAX_SQ_SIZE 取余。

```cpp
bool IsFull(SqQueue q) {
    return (q.rear + 1) % MAX_SQ_SIZE == q.front;
} 
```

## 求长度

```cpp
int Length(SqQueue q) {
    return (q.rear - q.front + MAX_SQ_SIZE) % MAX_SQ_SIZE;
}
```

## 入队

rear 始终指向最新入队元素的下一个元素，这意味着除非队列已满，否则 rear 必定指向一个空元素。

```cpp
Status Push(SqQueue &q, Elemtype elem) {
    if((q.rear + 1) % MAX_SQ_SIZE == q.front)
        return ERROR;
    q.base[q.rear] = elem;
    q.rear = (q.rear + 1) % MAX_SQ_SIZE;
    return OK;
}
```

## 出队

```cpp
Status Pop(SqQueue &q, Elemtype &elem) {
    if(q.front == q.rear)
        return ERROR;
    elem = q.base[q.front];
    q.front = (q.front + 1) % MAX_SQ_SIZE;
    return OK;
}
```

## 取头元素

```cpp
Status Top(SqQueue q, Elemtype &elem) {
    if(q.front == q.rear)
        return ERROR;
    elem = q.base[q.front];
    return OK;
}
```