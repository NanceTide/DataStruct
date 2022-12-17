#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 50
 
typedef struct node *EdgeNode;
typedef struct vnode *VertexNode;
typedef struct graph *ALGraph;
 
struct node { 
    int adjvex; 
    EdgeNode next;
};
 
struct vnode {
    int vertex;
    EdgeNode firstedge;
};
 
struct graph {
    struct vnode *adjlist;
    int n;
    int e;
};
 
void CreatALGraph(ALGraph G) {
    int i, j, k;
    int a;
    
    EdgeNode s;
    scanf("%d %d", &i, &j);
    G->n = i;
    G->e = j;

    for(i = 1; i <= G->n; i++) {
        scanf("%d", &a);
        G->adjlist[i].vertex = a;
        G->adjlist[i].firstedge = NULL;
    }
 
    for(k = 0; k < G->e; k++) {
    scanf("%d %d", &i, &j);
    s = (node*) malloc(sizeof(node));
    s->adjvex = j; 
    s->next = G->adjlist[i].firstedge;
    G->adjlist[i].firstedge = s;
    }
 
}
 
int main() {
 
    int i, j;
    ALGraph G = (graph*) malloc (sizeof(graph));
    G->adjlist = (vnode *)malloc(sizeof(vnode) * MaxVertexNum);
    
    CreatALGraph(G);
    
    for(i = 1; i <= G->n; i++) {
        while(G->adjlist[i].firstedge) {
            printf("%d -> ", G->adjlist[i].vertex);
            printf("%d\n", G->adjlist[i].firstedge->adjvex);
            G->adjlist[i].firstedge = G->adjlist[i].firstedge->next;
        }
    }
    return 0;
 
}