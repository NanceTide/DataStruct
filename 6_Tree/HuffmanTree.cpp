#include <iostream>
#include <string.h>
using namespace std;

typedef struct HTNode {
    int weight;
    int parent, lchild, rchild;
}*HuffmanTree;
typedef char **HuffmanCode;

void Select(HuffmanTree HT, int end, int &s1, int &s2) {
    int min1, min2, i;
    
    for(i = 1; HT[i].parent != 0 && i <= end; i++);
    s1 = i; min1 = HT[i].weight;

    for(i++; HT[i].parent != 0 && i <= end; i++);
    s2 = i; min2 = HT[i].weight;

    if(min1 > min2) {
        swap(min1, min2);
        swap(s1, s2);
    }

    for(i++; i <= end; i++) {
        if(HT[i].parent != 0)
            continue;
        if(HT[i].weight < min1) {
            min2 = HT[i].weight;
            s2 = i;
            swap(min1, min2);
            swap(s1, s2);
        } else if (HT[i].weight < min2 && HT[i].weight >= min1) {
            min2 = HT[i].weight;
            s2 = i;
        }
    }
}

void CreateHuffmanTree(HuffmanTree &HT, int *arr, int n) {
    if(n <= 1)
        return;
    int m = 2 * n - 1;
    HT = (HuffmanTree) malloc ((m + 1) * sizeof(HTNode));
    for(int i = 1; i <= n; i++) {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].weight = arr[i - 1];
    }
    for(int i = n + 1; i <= m; i++)
        HT[i].parent = 0;
    for(int i = n + 1; i <= m; i++) {
        int s1, s2;
        Select(HT, i - 1, s1, s2);
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void HuffmanCoding(HuffmanTree HT, HuffmanCode &HC, int n) {
    HC = (HuffmanCode) malloc ((n + 1) * sizeof(char*));
    char *cd = (char*) malloc (n * sizeof(char));
    cd[n - 1] = '\0';
    for(int i = 1; i <= n; i++) {
        int start = n - 1;
        for(int prev = i, curr = HT[i].parent; curr != 0; prev = curr, curr = HT[curr].parent) {
            start--;
            if(HT[curr].lchild == prev)
                cd[start] = '0';
            else
                cd[start] = '1';
        }
        HC[i] = (char*) malloc ((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    free(cd);
}

int main() {

    HuffmanTree HT;
    HuffmanCode HC;
    int arr[5] = {6, 7, 2, 5, 8};
    CreateHuffmanTree(HT, arr, 5);
    HuffmanCoding(HT, HC, 5);
    cout << HC[2];

    return 0;

}