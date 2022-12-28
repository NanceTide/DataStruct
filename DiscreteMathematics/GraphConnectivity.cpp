#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<vector<int>> operator*(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    int num = a.size();
    vector<vector<int>> ans(num, vector<int>(num, 0));
    for(int i = 0; i < num; i++) {
        for(int j = 0; j < num; j++) {
            for(int k = 0; k < num; k++) {
                ans[i][j] |= a[i][k] & b[k][j];
            }
        }
    }
    return ans;
}

vector<vector<int>> operator|(vector<vector<int>> &a, vector<vector<int>> &b) {
    int num = a.size();
    vector<vector<int>> ans(num, vector<int>(num, 0));
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j < a.size(); j++) {
            ans[i][j] = a[i][j] | b[i][j];
        }
    }
    return ans;
}

bool is_connected(vector<vector<int>> graph) {
    for(auto i : graph) {
        for(auto j : i) {
            if(!j)
                return false;
        }
    }
    return true;
}

int main() {

    int num;
    cout << "给出图的阶。\n";
    cin >> num;

    vector<vector<int>> strong_graph(num, vector<int>(num, 0));
    vector<vector<int>> weak_graph(num, vector<int>(num, 0));

    string in;
    cout << "结点从 0 到 " << num - 1 << " 编号。请输入数字来代表顶点，两两一组。其中，靠前的数字邻接到靠后的数字上。\n";
    cin >> in;

    for(int i = 1; i < in.size(); i += 2) {
        strong_graph[in[i - 1] - '0'][in[i] - '0'] = 1;
    }

    for(int i = 1; i < in.size(); i += 2) {
        weak_graph[in[i - 1] - '0'][in[i] - '0'] = 1;
        weak_graph[in[i] - '0'][in[i - 1] - '0'] = 1;
    }

    set<vector<vector<int>>> strong_graph_set;
    strong_graph_set.insert(strong_graph);
    vector<vector<int>> strong_tmp = strong_graph * strong_graph;
    vector<vector<int>> strong_ans = strong_graph | strong_tmp;
    while(!strong_graph_set.count(strong_tmp)) {
        strong_graph_set.insert(strong_tmp);
        strong_tmp = strong_tmp * strong_graph;
        strong_ans = strong_ans | strong_tmp;
    }
    bool strong_flag = is_connected(strong_ans);

    set<vector<vector<int>>> weak_graph_set;
    weak_graph_set.insert(weak_graph);
    vector<vector<int>> weak_tmp = weak_graph * weak_graph;
    vector<vector<int>> weak_ans = weak_graph | weak_tmp;
    while(!weak_graph_set.count(weak_tmp)) {
        weak_graph_set.insert(weak_tmp);
        weak_tmp = weak_tmp * weak_graph;
        weak_ans = weak_ans | weak_tmp;
    }
    bool weak_flag = is_connected(weak_ans);

    if(strong_flag)
        cout << "该图强连通。";
    else if(weak_flag)
        cout << "该图弱连通。";
    else
        cout << "该图不连通。";

    return 0;

}