#include <ios>
#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int index(char chr, set<char> elem_set) {
    int index = 0;
    for(auto i : elem_set) {
        if(i == chr)
            return index;
        index++;
    }
    return -1;
}

void prt(set<char> elem_set, vector<vector<int>> rel_vec) {
    auto elem_set_iter = elem_set.begin();
    cout << "\\ ";
    for(auto i: elem_set)
        cout << i << ' ';
    cout << '\n';
    for(auto i : rel_vec) {
        cout << *(elem_set_iter++) << ' ';
        for(auto j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}

bool is_reflexive(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        if(!rel_vec[i][i])
            return false;
    }
    return true;
}

bool is_antireflexive(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        if(rel_vec[i][i])
            return false;
    }
    return true;
}

bool is_symmetric(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < i; j++) {
            if(rel_vec[i][j] != rel_vec[j][i])
                return false;
        }
    }
    return true;
}

bool is_antisymmetric(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < i; j++) {
            if(rel_vec[i][j] && rel_vec[j][i])
                return false;
        }
    }
    return true;
}

bool is_transitive(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            for(int k = 0; k < len; k++) {
                if(rel_vec[i][j] && rel_vec[j][k])
                    if(!rel_vec[i][k])
                        return false;
            }
        }
    }
    return true;
}

vector<vector<int>> reflexive_closure(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++)
        rel_vec[i][i] = 1;
    return rel_vec;
}

vector<vector<int>> symmetric_closure(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            if(rel_vec[i][j])
                rel_vec[j][i] = 1;
        }
    }
    return rel_vec;
}

vector<vector<int>> transitive_closure(vector<vector<int>> rel_vec) {
    int len = rel_vec.size();
    bool next = true;
    while(next) {
        next = false;
        for(int i = 0; i < len; i++) {
            for(int j = 0; j < len; j++) {
                for(int k = 0; k < len; k++) {
                    if(rel_vec[i][j] && rel_vec[j][k])
                        if(!rel_vec[i][k]) {
                            rel_vec[i][k] = 1;
                            next = true;
                        }
                }
            }
        }
    }
    return rel_vec;
}

int main() {

    set<char> elem_set;
    string in;
    cout << "??????????????????????????????????????????\n";
    cin >> in;
    for(auto c: in) {
        if(c == ' ' || c == '\n')
            continue;
        elem_set.insert(c);
    }

    vector<char> elem_vec;
    for(auto c: elem_set)
        elem_vec.push_back(c);
    vector<vector<int>> rel_vec(elem_set.size(), vector<int>(elem_set.size(), 0));

    cout << "????????????????????????????????????????????????????????????????????????\n";
    cin >> in;
    for(int i = 1; i < in.length(); i += 2) {
        if(!elem_set.count(in[i - 1]) || !elem_set.count(in[i])) {
            cout << "??????????????????????????????????????????\n";
            exit(-1);
        }
        rel_vec[index(in[i - 1], elem_set)][index(in[i], elem_set)] = 1;
    }

    prt(elem_set, rel_vec);

    cout << boolalpha;
    cout << "?????????: " << is_reflexive(rel_vec) << '\n';
    cout << "????????????: " << is_antireflexive(rel_vec) << '\n';
    cout << "?????????: " << is_symmetric(rel_vec) << '\n';
    cout << "????????????: " << is_antisymmetric(rel_vec) << '\n';
    cout << "?????????: " << is_transitive(rel_vec) << '\n';
    cout << "????????????: \n";
    prt(elem_set, reflexive_closure(rel_vec));
    cout << '\n';
    cout << "????????????: \n";
    prt(elem_set, symmetric_closure(rel_vec));
    cout << '\n';
    cout << "????????????: \n";
    prt(elem_set, transitive_closure(rel_vec));
    cout << '\n';

}