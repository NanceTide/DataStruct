#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
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
    map<char, int> alpha_map;
    string str_origin;
    string str_aftercode;
    string str_decode;
    getline(cin, str_origin);

    for(auto c: str_origin) {
        if(alpha_map.count(c) == 0)
            alpha_map[c] = 1;
        else 
            alpha_map[c]++;
    }

    int *weight_arr = (int*) malloc (sizeof(int) * alpha_map.size());
    char *alpha_arr = (char*) malloc (sizeof(char) * alpha_map.size());
    
    int index = 0;
    for(auto c : alpha_map) {
        alpha_arr[index] = c.first;
        weight_arr[index] = c.second;
        index++;
    }

    CreateHuffmanTree(HT, weight_arr, alpha_map.size());
    HuffmanCoding(HT, HC, alpha_map.size());
    
    map<char, string> HC_charstring;
    for(int i = 0; i < alpha_map.size(); i++) {
        HC_charstring[alpha_arr[i]] = HC[i + 1];
    }

    for(auto c : HC_charstring) {
        cout << c.first << ' ' << c.second << '\n';
    }

    for(auto c : str_origin) {
        str_aftercode += HC_charstring[c];
    }

    cout << str_aftercode << '\n';

    cout << str_origin;
    
    return 0;

}