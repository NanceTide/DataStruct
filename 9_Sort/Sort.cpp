#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <set>
using namespace std;

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

void Swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void Prt(vector<int> v) {
    for(auto c : v)
        cout << c << ' ';
    cout << '\n';
}

bool operator==(vector<int> a, vector<int> b) {
    if(a.size() != b.size())
        return false;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

void Test(void Func(vector<int>&)) {
    auto v = RandBetween(0, 100000, 1000);
    auto v_ = v;
    Func(v);
    sort(v_.begin(), v_.end());
    // Prt(v);
    cout << "IsSorted: " << is_sorted(v.begin(), v.end()) << '\n';
    cout << "IsEqual: " << (v == v_) << '\n';
    cout << '\n';
}

void TestWithout0(void Func(vector<int>&)) {
    auto v = RandBetween(0, 100000, 1000);
    v[0] = -1;
    auto v_ = v;
    Func(v);
    sort(v_.begin() + 1, v_.end());
    // Prt(v);
    v[0] = -1;
    v_[0] = -1;
    cout << "IsSorted: " << is_sorted(v.begin() + 1, v.end()) << '\n';
    cout << "IsEqual: " << (v == v_) << '\n';
    cout << '\n';
}

void BubbleSort(vector<int> &v) {
    for(int i = 0; i < v.size(); i++)
        for(int j = 0; j < i; j++)
            if(v[j] > v[i])
                Swap(v[i], v[j]);
}

void InsertSort(vector<int> &v) {
    for(int i = 1; i < v.size(); i++)
        for(int j = i; j > 0 && v[j] < v[j - 1]; j--)
            Swap(v[j], v[j - 1]);
}

void InsertSort_(vector<int> &v) {
    int i, j, x;
    for(i = 1; i < v.size(); i++){
        x = v[i];
        for(j = i - 1; j >= 0 && x < v[j]; j--)
            v[j + 1] = v[j];
        v[j + 1] = x;
    }
}

void BinaryInsertSort(vector<int> &v) {
    int i, j;
    for(i = 2; i < v.size(); i++) {
        v[0] = v[i];
        int lo = 1, hi = i - 1, mid;
        while(lo <= hi) {
            mid = (lo + hi) >> 1;
            if(v[0] < v[mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        for(j = i - 1; j >= hi + 1; j--)
            v[j + 1] = v[j];
        v[hi + 1] = v[0];
    }
}

int main() {

    cout << boolalpha;
    // Test(BubbleSort);
    // Test(InsertSort);
    // Test(InsertSort_);
    TestWithout0(BinaryInsertSort);
    return 0;

}