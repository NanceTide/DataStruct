# 二叉树的遍历算法

这些解释是由 ChatGPT 提供的。

## 递归算法 

### 前序遍历二叉树

1. 如果当前节点为空，则返回 OK。
2. 访问当前节点的值。
3. 递归遍历左子树。
4. 递归遍历右子树。

```cpp
PreOrderTraverse(BiTree root, Status (*Visit)(int elem)) 
```

### 中序遍历二叉树

1. 如果当前节点为空，则返回 OK。
2. 递归遍历左子树。
3. 访问当前节点的值。
4. 递归遍历右子树。

```cpp
InOrderTraverse(BiTree root, Status (*Visit)(int elem))
```

### 后序遍历二叉树

1. 如果当前节点为空，则返回 OK。
2. 递归遍历左子树。
3. 递归遍历右子树。
4. 访问当前节点的值。

```cpp
PostOrderTraverse(BiTree root, Status (*Visit)(int elem))
```

## 非递归算法

### 基于栈的前序遍历二叉树

1. 如果当前节点为空，则返回 OK。
2. 将当前节点压入栈中。
3. 循环执行以下操作：
   1. 将栈顶节点弹出。
   2. 访问该节点的值。
   3. 如果该节点有右子树，则将右子树压入栈中。
   4. 如果该节点有左子树，则将左子树压入栈中。

```cpp
PreOrderTraverse_(BiTree root, Status (*Visit)(int elem)) 
```

### 基于栈的中序遍历二叉树：

1. 如果当前节点为空，则返回 OK。
2. 循环执行以下操作：
   1. 如果当前节点有左子树，则将左子树压入栈中，然后将当前节点设为左子树。
   2. 否则，将栈顶节点弹出并访问。然后将当前节点设为右子树。

```cpp
InOrderTraverse_(BiTree root, Status (*Visit)(int elem))
```

### 基于栈的后序遍历二叉树

1. 如果当前节点为空，则返回 OK。
2. 将当前节点压入栈中。
3. 循环执行以下操作：
   1. 将栈顶节点弹出并将其压入答案栈中。
   2. 如果栈顶节点有左子树，则将左子树压入栈中。
   3. 如果栈顶节点有右子树，则将右子树压入栈中。
   4. 将答案栈中的所有节点依次弹出并访问。

```cpp
PostOrderTraverse_(BiTree root, Status (*Visit)(int elem))
```

### 基于队列的层次遍历二叉树

1. 如果当前节点为空，则返回 ERROR。
2. 将当前节点压入队列中。
3. 循环执行以下操作：
   1. 将队列头节点弹出并访问。
   2. 如果队列头节点有左子树，则将左子树压入队列中。
   3. 如果队列头节点有右子树，则将右子树压入队列中。

```cpp
LevelOrderTraverse(BiTree root, Status (*Visit)(int elem))
```
