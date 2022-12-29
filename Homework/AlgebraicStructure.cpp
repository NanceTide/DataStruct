#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

bool is_commutative(vector<vector<char>> ans_vec) {
    int len = ans_vec.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < i; j++) {
            if(ans_vec[i][j] != ans_vec[j][i])
                return false;
        }
    }
    return true;
}

int return_index(char chr, set<char> oper_set) {
    int index = 0;
    for(auto c: oper_set) {
        if(c == chr)
            return index;
        index++;
    }
    return -1;
}

bool is_associative(vector<vector<char>> ans_vec, set<char> oper_set) {
    int len = oper_set.size();
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            for(int k = 0; k < len; k++) {
                if(oper_set.count(ans_vec[i][j]) && oper_set.count(ans_vec[j][k])) {
                    int index_ij = return_index(ans_vec[i][j], oper_set);
                    int index_jk = return_index(ans_vec[j][k], oper_set);
                    if(ans_vec[index_ij][k] != ans_vec[i][index_jk])
                        return false;
                }
            }
        }
    }
    return true;
}

char left_identity_element(vector<vector<char>> ans_vec, vector<char> oper_vec) {
    int len = oper_vec.size();
    bool flag = true;
    for(int i = 0; i < len; i++) {
        flag = true;
        for(int j = 0; j < len; j++) {
            if(ans_vec[i][j] != oper_vec[j]) {
                flag = false;
                break;
            }
        }
        if(flag)
            return oper_vec[i];
    }

    return '\0';
}

char right_identity_element(vector<vector<char>> ans_vec, vector<char> oper_vec) {
    int len = oper_vec.size();
    bool flag = true;
    for(int j = 0; j < len; j++) {
        flag = true;
        for(int i = 0; i < len; i++) {
            if(ans_vec[i][j] != oper_vec[i]) {
                flag = false;
                break;
            }
        }
        if(flag)
            return oper_vec[j];
    }
    return '\0';
}

char left_zero_element(vector<vector<char>> ans_vec, vector<char> oper_vec) {
    int len = oper_vec.size();
    bool flag = true;
    for(int i = 0; i < len; i++) {
        flag = true;
        for(int j = 0; j < len; j++) {
            if(ans_vec[i][j] != oper_vec[i]) {
                flag = false;
                break;
            }
        }
        if(flag)
            return oper_vec[i];
    }
    return '\0';
}

char right_zero_element(vector<vector<char>> ans_vec, vector<char> oper_vec) {
    int len = oper_vec.size();
    bool flag = true;
    for(int j = 0; j < len; j++) {
        flag = true;
        for(int i = 0; i < len; i++) {
            if(ans_vec[i][j] != oper_vec[j]) {
                flag = false;
                break;
            }
        }
        if(flag)
            return oper_vec[j];
    }
    return '\0';
}

map<char, set<char>> right_inverse_element(vector<vector<char>> ans_vec, vector<char> oper_vec, char identity_element) {
    int len = oper_vec.size();
    map<char, set<char>> ans;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            if(ans_vec[i][j] == identity_element) {
                ans[oper_vec[i]].insert(oper_vec[j]);
            }
        }
    }
    return ans;
}

map<char, set<char>> left_inverse_element(vector<vector<char>> ans_vec, vector<char> oper_vec, char identity_element) {
    int len = oper_vec.size();
    map<char, set<char>> ans;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            if(ans_vec[i][j] == identity_element) {
                ans[oper_vec[j]].insert(oper_vec[i]);
            }
        }
    }
    return ans;
}

int main() {

    string in;
    getline(cin, in);
    istringstream scin(in);
    set<char> oper_set;
    vector<char> oper_vec;
    char c;
    while(scin >> c) {
        oper_set.insert((c));
    }

    cout << "A 内含元素: ";
    for(auto c : oper_set) {
        oper_vec.push_back(c);
        cout << c << ' ';
    }
    cout << '\n';
    cout << "请按照以上打印的顺序依次输入每一代数式的答案。\n";

    bool closure_flag = true;
    int ans_num;
    vector<vector<char>> ans_vec(oper_set.size());
    for(ans_num = 0; ans_num < oper_set.size() * oper_set.size(); ans_num++) {
        do {
            cin >> c;
        } while(c == ' ' || c == '\n');
        ans_vec[ans_num / oper_set.size()].push_back(c);
        if(oper_set.count(c) == 0)
            closure_flag = false;
    }

    cout << "运算表:\n\\ ";
    auto oper_vec_iter = oper_vec.begin();
    for(auto c: oper_vec) {
        cout << c << ' ';
    }
    cout << '\n';
    for(auto arr : ans_vec) {
        cout << *(oper_vec_iter++) << ' ';
        for(auto c : arr)
            cout << c << ' ';
        cout << '\n';
    }

    bool commutative_flag, associative_flag, identity_flag, zero_flag, inverse_flag;
    char lc, rc;

    cout << boolalpha;
    cout << "元素的阶: " << oper_vec.size() << '\n';
    cout << "封闭性: " << closure_flag << '\n';
    cout << "交换性: " << (commutative_flag = is_commutative(ans_vec)) << '\n';
    cout << "结合性: " << (associative_flag = is_associative(ans_vec, oper_set)) << '\n';

    char identity_element = '\0';
    lc = left_identity_element(ans_vec, oper_vec);
    rc = right_identity_element(ans_vec, oper_vec);
    if((identity_flag = (lc == rc && lc != '\0')))
        cout << "幺元: " << (identity_element = lc) << '\n';

    char zero_element;
    lc = left_zero_element(ans_vec, oper_vec);
    rc = right_zero_element(ans_vec, oper_vec);
    if((zero_flag = (lc == rc && lc != '\0')))
        cout << "零元: " << (zero_element = lc) << '\n';

    auto right_inverse_element_map = right_inverse_element(ans_vec, oper_vec, identity_element);
    if(identity_flag) {
        cout << "右逆元:\n";
        for(auto i : right_inverse_element_map) {
            cout << "    " << i.first << ": ";
            for(auto j : i.second) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    }
    auto left_inverse_element_map = left_inverse_element(ans_vec, oper_vec, identity_element);
    if(identity_flag) {
        cout << "左逆元:\n";
        for(auto i : left_inverse_element_map) {
            cout << "    " << i.first << ": ";
            for(auto j : i.second) {
                cout << j << ' ';
            }
            cout << '\n';
        }
    }
    inverse_flag = right_inverse_element_map.size() == left_inverse_element_map.size() && right_inverse_element_map.size() == oper_set.size();

    cout << "半群: " << (closure_flag && associative_flag) << '\n';
    cout << "独异点: " << (closure_flag && associative_flag && identity_flag) << '\n';
    cout << "群: " << (closure_flag && associative_flag && identity_flag && inverse_flag) << '\n';
    cout << "交换群: " << (closure_flag && associative_flag && identity_flag && inverse_flag && commutative_flag )<< '\n';
    
    return 0;

}