#include <iostream>
#include <set>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
using namespace std;

class has_cycle {
public:
    vector<int> visited;
    vector<vector<int>> graph;

    has_cycle(vector<vector<int>> graph) : graph(graph), visited(graph.size(), 0) {}

    bool operator()() {
        for(int i = 0; i < graph.size(); i++)
            if(!visited[i])
                if(has_cycle_traverse(i))
                    return true;
        return false;
    }

    bool has_cycle_traverse(int i) {
        visited[i] = 1;
        for(int j = i + 1; j < graph.size(); j++) {
            if(graph[i][j] != 0 && i != j) {
                if(!visited[j]) {
                    if(has_cycle_traverse(j))
                        return true;
                } else {
                    return true;
                }
            }
        }
        return false;
    } 
};

int main() {

    int num;
    cout << "给出图的阶。\n";
    cin >> num;

    vector<vector<int>> graph(num, vector<int>(num, 0));
    cout << "结点从 0 到 " << num - 1 << " 编号。请输入数字来代表顶点，三个一组。其中，前两个数字相互邻接，后一个数字代表权重。当您想结束时，将第一个数字输入为 -1。\n";
    cout << "注意您必须输入一个简单连通图。\n";

    multimap<int, pair<int, int>> edge_map;

    int num1, num2, num3;
    while(true) {
        cin >> num1;
        if(num1 == -1)
            break;
        cin >> num2 >> num3;
        graph[num1][num2] = num3;
        graph[num2][num1] = num3;
        edge_map.insert({num3, {num1, num2}});
    }
     
    vector<vector<int>> tree(num, vector<int>(num, 0));

    int num_edge = 0;
    for(auto i : edge_map) {
        tree[i.second.first][i.second.second] = i.first;
        tree[i.second.second][i.second.first] = i.first;
        if(has_cycle(tree)()) {
            tree[i.second.first][i.second.second] = 0;
            tree[i.second.second][i.second.first] = 0;
        }
        else
            num_edge++;
        if(num_edge >= num - 1)
            break;
    }

    cout << "给出最小生成树：\n";
    for(auto i: tree) {
        for(auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }

}