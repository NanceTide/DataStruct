#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_STACK_SIZE 128
#define MAX_SQ_SIZE 128
typedef int Status;

#define MVNum 100
typedef char VerTexType;
typedef int ArcType;
struct AMGraph {
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
};

int LocateVex(AMGraph G, VerTexType elem) {
    for(int i = 0; i < G.vexnum; i++)
        if(G.vexs[i] == elem)
            return i;
    return -1;
}

Status CreateUDN(AMGraph &G) {
    cin >> G.vexnum >> G.arcnum;
    for(int i = 0; i < G.vexnum; i++)
        cin >> G.vexs[i];
    for(int i = 0; i < G.vexnum; i++)
        for(int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = INT_MAX;
    VerTexType vi, vj;
    ArcType w;
    for(int k = 0; k < G.arcnum; k++) {
        cin >> vi >> vj >> w;
        int i = LocateVex(G, vi);
        int j = LocateVex(G, vj);
        G.arcs[i][j] = w;
        G.arcs[j][i] = w;
    }
    return OK;
}

Status Prt(AMGraph G) {
    cout << "\\ ";
    for(int i = 0; i < G.vexnum; i++)
        cout << G.vexs[i] << ' ';
    cout << '\n';
    for(int i = 0; i < G.vexnum; i++) {
        cout << G.vexs[i] << ' ';
        for(int j = 0; j < G.vexnum; j++) {
            if(G.arcs[i][j] == INT_MAX)
                cout << '\\' << ' ';
            else 
                cout << G.arcs[i][j] << ' ';
        }
        cout << '\n';
    }
    return OK;
}

struct ArcNode {
    int adjvex;
    ArcType weight;
    ArcNode *next;
};

typedef struct VNode {
    VerTexType data;
    ArcNode *first;
}AdjList[MVNum];

struct ALGraph {
    AdjList vexs;
    int vexnum;
    int arcnum;
};

int LocateVex(ALGraph G, VerTexType elem) {
    for(int i = 0; i < G.vexnum; i++)
        if(G.vexs[i].data == elem)
            return i;
    return -1;
}

Status CreateUDN(ALGraph &G) {
    cin >> G.vexnum >> G.arcnum;
    for(int i = 0; i < G.vexnum; i++) {
        cin >> G.vexs[i].data;
        G.vexs[i].first = nullptr;
    }
    VerTexType vi, vj;
    ArcType w;
    for(int k = 0; k < G.arcnum; k++) {
        cin >> vi >> vj >> w;
        int i = LocateVex(G, vi);
        int j = LocateVex(G, vj);
        auto pi = new ArcNode;
        auto pj = new ArcNode;
        pi->weight = w;
        pj->weight = w;
        pi->adjvex = j;
        pj->adjvex = i;
        pi->next = G.vexs[i].first;
        pj->next = G.vexs[j].first;
        G.vexs[i].first = pi;
        G.vexs[j].first = pj;
    }
    return OK;
}

Status Prt(ALGraph G) {
    for(int i = 0; i < G.vexnum; i++) {
        cout << G.vexs[i].data << " -> ";
        auto p = G.vexs[i].first;
        while(p) {
            cout << G.vexs[p->adjvex].data << ',' << p->weight << "; ";
            p = p->next;
        }
        cout << '\n';
    }
    return OK;
}

int main() {

    AMGraph AMGraph0;
    CreateUDN(AMGraph0);
    Prt(AMGraph0);

    ALGraph ALGraph0;
    CreateUDN(ALGraph0);
    Prt(ALGraph0);

    return 0;

}