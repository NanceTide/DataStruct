# 图的遍历

从已给的连通图中的某一顶点出发，沿着一些边访遍中所有的顶点，且使每个顶点仅被访问一次，就叫做图的遍历。它是图的基本运算。

在图的遍历中，我们可能会重复访问已访问过的结点。解决方法是设置一个辅助数组 visited[n]，用来标记每个被访问过的节点。这个数组初始状态置 0，访问过后置 1。

## 深度优先搜索 DFS

深度优先搜索算法(Depth First Search, DFS)的思想可简要描述为对于每一个可能的分支路径深入到不能深入为止。在此过程中，每个结点只能被访问一次。

1. 从图中指定结点 v 出发，访问此节点，然后依次从 v 的未被访问的邻接点出发深度优先遍历，直至图中所有与 v 有路径连通的顶点都被访问到。
2. 若此时图中尚有顶点未被访问，则选图中一个未曾被访问的顶点作起始点，重复步骤 1，直至图中所有顶点都被访问为止。

深度优先搜索在不同图实现的效率不同。  
|图实现|邻接矩阵|邻接表|
|:-:|:-:|:-:|
|时间复杂度|$O(n^2)$|$O(n+e)$|

TODO: 复杂度待查证

### 递归遍历邻接矩阵

```cpp
void DepthFirstSearchTraverse(AMGraph G) {
    int n = G.vexnum;
    bool visited[];
    for(int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for(int i = 0; i < G.vexnum; i++)
        if(!visited[i])
            DFS(i);
}

void DFS(int i, AMGraph G, bool *visited) {
    visited[i] = true;
    for(int j = 0; j < G.vexnum; j++)
        if(G.arcs[i][j] != 0 && !visited[j])
            DFS(j);
}
```

### 迭代遍历邻接矩阵

递归太深可能造成堆栈的溢出。当图比较大的时候，这一点很可能发生。利用栈代替函数递归可以以非递归的方式实现 DFS。

```cpp
void DepthFirstSearchTraverse(AMGraph G) {
    stack<int> st;
    bool visited[];
    for(int i = 0; i < G.vexnum; i++)
        visited[i] = false;
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i])
    }
}
```

## 广度优先搜索 BFS


