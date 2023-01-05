#include <ctime>
#include <stack>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

struct SStable {
    int *elem;
    int len;
};

vector<int> RandBetween(int l, int r, int len) {
    default_random_engine e(time(0)); 
    uniform_int_distribution<int> u(l, r);
    vector<int> vec;
    for(int i = 0; i < len; i++)
        vec.push_back(u(e));
    return vec;
}

vector<int> RangeInt(int l, int r) {
    vector<int> vec;
    for(; l < r; l++)
        vec.push_back(l);
    return vec;
}

void Init(SStable &arr, vector<int> vec) {
    arr.elem = new int[vec.size() + 1];
    for(int i = 0; i < vec.size(); i++)
        arr.elem[i + 1] = vec[i];
    arr.len = vec.size();
}

int OrderSearch(SStable arr, int key) {
    arr.elem[0] = key;
    int i;
    for(i = arr.len; arr.elem[i] != key; i--);
    return i;
}

int BinarySearch(SStable arr, int key, int lo, int hi) {
    if(lo > hi)
        return 0;
    int mid = (lo + hi) >> 1;
    if(key == arr.elem[mid])
        return mid;
    else if(key < arr.elem[mid])
        return BinarySearch(arr, key, lo, mid - 1);
    else if(key > arr.elem[mid])
        return BinarySearch(arr, key, mid + 1, hi);
    return 0;
}

int BinarySearch(SStable arr, int key) {
    int lo = 1, hi = arr.len, mid;
    while(lo <= hi) {
        mid = (lo + hi) >> 1;
        if(key == arr.elem[mid])
            return mid;
        else if(key < arr.elem[mid])
            hi = mid - 1;
        else if(key > arr.elem[mid])
            lo = mid + 1;
    }
    return 0;
}

typedef struct BSTNode {
    int data;
    BSTNode *lchild, *rchild;
}*BSTree;

void Insert(BSTree &root, int data) {
    if(!root) {
        root = new BSTNode;
        root->data = data;
        root->lchild = nullptr;
        root->rchild = nullptr;
    }
    BSTree tmp = root;
    BSTree pre = nullptr;
    while(tmp) {
        pre = tmp;
        if(tmp->data == data)
            return;
        else if(data < tmp->data)
            tmp = tmp->lchild;
        else if(data > tmp->data)
            tmp = tmp->rchild;
    }
    if(data < pre->data) {
        pre->lchild = new BSTNode;
        pre->lchild->data = data;
        pre->lchild->lchild = nullptr;
        pre->lchild->rchild = nullptr;
    }else if(data > pre->data) {
        pre->rchild = new BSTNode;
        pre->rchild->data = data;
        pre->rchild->lchild = nullptr;
        pre->rchild->rchild = nullptr;
    }
}

BSTree BSTSearch(BSTree root, int data) {
    if(!root || root->data == data)
        return root;
    else if(data < root->data)
        return BSTSearch(root->lchild, data);
    else
        return BSTSearch(root->rchild, data);
}

void Init(BSTree &root, vector<int> vec) {
    for(auto c : vec)
        Insert(root, c);
}

void InOrderTraverse(BSTree root) {
    if(!root)
        return;
    InOrderTraverse(root->lchild);
    cout << root->data << ' ';
    InOrderTraverse(root->rchild);
}

BSTree DeleteMin(BSTree &root) {
    if(!root->lchild) {
        BSTree t = root;
        root = root->rchild;
        return root;
    }
    root->lchild = DeleteMin(root->lchild);
    return root;
}

BSTree DeleteEqual(BSTree &root, int data) {
    if(!root)
        return nullptr;
    if(data < root->data)
        root->lchild = DeleteEqual(root->lchild, data);
    else if(data > root->data)
        root->rchild = DeleteEqual(root->rchild,data);
    else if(data == root->data) {
        if(!root->lchild)
            return root->rchild;
        if(!root->rchild)
            return root->lchild;
        BSTree t = root;
        root = root->rchild;
        while(root->lchild)
            root = root->lchild;
        root->rchild = DeleteMin(t->rchild);
        root->lchild = t->lchild;
    }
    return root;
}

int main() {

    // SStable sstable;

    // Init(sstable, RandBetween(0, INT_MAX, 1000000));
    // sstable.elem[1] = -1;
    // cout << OrderSearch(sstable, -1);

    // auto vec = RangeInt(1, 1000000);
    // Init(sstable, vec);
    // cout << BinarySearch(sstable, 25000);
    // cout << BinarySearch(sstable, 25000, 1, sstable.len);

    BSTree bstree;
    vector<int> a;
    a = RangeInt(0, 200);
    random_shuffle(a.begin(), a.end());
    Init(bstree, a);
    InOrderTraverse(bstree);
    cout << '\n';
    DeleteEqual(bstree, 10);
    InOrderTraverse(bstree);
    return 0;

}