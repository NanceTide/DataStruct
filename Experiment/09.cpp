#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <cctype>
#include <random>
#include <cstdlib>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T> class SortList{
protected:
    vector<T> vT;
    int start;
    int stop;
public:
    SortList(vector<T> _vT) : vT(_vT) {}
    SortList add(T object) {vT.push_back(object); return *this;}
    virtual void sort() {};
    void sortStart() {start = clock();}
    void sortStop() {stop = clock(); printf("Time use: %d\n", stop - start);}
    T& operator[](int index) {return vT[index];}
    void printInt() {for(T object : vT) printf("%d\n", object);}
};

template <typename T> class BubbleSort : public SortList<T>{
public:
    BubbleSort(vector<T> _vT) : SortList<T>(_vT) {}
    void sort(){  
        SortList<T>::sortStart();
        for(int i = 0; i < SortList<T>::vT.size() - 1; i++)
            for(int j = 0; j < SortList<T>::vT.size() - i - 1; j++)
                if((*this)[j] > (*this)[j + 1])
                    swap((*this)[j], (*this)[j + 1]);
        SortList<T>::sortStop();
    }
};

template <typename T> class InsertSort : public SortList<T>{
public:
    InsertSort(vector<T> _vT) : SortList<T>(_vT) {}
    void sort(){
        SortList<T>::sortStart();
        for(int i = 1; i < SortList<T>::vT.size(); i++)
            for(int j = i; j > 0 && (*this)[j - 1] > (*this)[j]; j--)
                swap((*this)[j - 1], (*this)[j]);
        SortList<T>::sortStop();
    }
};

template <typename T> class SelectionSort : public SortList<T>{
public:
    SelectionSort(vector<T> _vT) : SortList<T>(_vT) {}
    void sort(){
        SortList<T>::sortStart();
        for(int i = 0; i < SortList<T>::vT.size(); i++){
            int minindex = i;
            for(int j = i; j < SortList<T>::vT.size(); j++){
                if((*this)[minindex] > (*this)[j])
                    minindex = j;
            }
            swap((*this)[minindex], (*this)[i]);
        }
        SortList<T>::sortStop();
    }
};

template <typename T> class ShellSort : public SortList<T>{
public:
    ShellSort(vector<T> _vT) : SortList<T>(_vT) {}
    void sort(){

    }
};

template <typename T> class MergeSort : public SortList<T>{
private:
    vector<T> tmp;
    int insertLimit = 7;
    int extraSize = 8;
public:
    MergeSort(vector<T> _vT) : SortList<T>(_vT){}
    void sort(){
        SortList<T>::sortStart();
        tmp.resize(SortList<T>::vT.size());
        _sort(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort(int lo, int hi){
        if(lo >= hi)
            return;
        int mid = lo + ((hi - lo) >> 1);
        _sort(lo, mid);
        _sort(mid + 1, hi);
        merge(lo, mid, hi);
    }
    void merge(int lo, int mid, int hi){
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            tmp[k] = (*this)[k];
        for(int k = lo; k <= hi; k++)
            if(i > mid)
                (*this)[k] = tmp[j++];
            else if(j > hi)
                (*this)[k] = tmp[i++];
            else if(tmp[i] > tmp[j])
                (*this)[k] = tmp[j++];
            else
                (*this)[k] = tmp[i++];
    }

 // 2.2.10
    void sort10(){
        SortList<T>::sortStart();
        tmp.resize(SortList<T>::vT.size());
        _sort10(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort10(int lo, int hi){
        if(lo >= hi)
            return;
        int mid = lo + ((hi - lo) >> 1);
        _sort10(lo, mid);
        _sort10(mid + 1, hi);
        merge10(lo, mid, hi);
    }
    void merge10(int lo, int mid, int hi){
        int i = lo, j = hi;
        for(int k = lo; k <= mid; k++)
            tmp[k] = (*this)[k];
        for(int k = mid + 1; k <= hi; k++)
            tmp[k] = (*this)[hi - (k - mid - 1)];
        for(int k = lo; k <= hi; k++)
            if(tmp[i] < tmp[j])
                (*this)[k] = tmp[i++];
            else if(tmp[i] >= tmp[j])
                (*this)[k] = tmp[j--];
    }

 // 2.2.11
    void sort11(){
        SortList<T>::sortStart();
        tmp.resize(SortList<T>::vT.size());
        _sort11(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort11(int lo, int hi){
        if(lo >= hi)
            return;
        else if(hi - lo < insertLimit)
        {
            insertSort(lo, hi);
            return;
        }
        int mid = lo + ((hi - lo) >> 1);
        _sort11(lo, mid);
        _sort11(mid + 1, hi);
        if((*this)[mid] > (*this)[mid + 1])
            merge11(lo, mid, hi);
    }
    void merge11(int lo, int mid, int hi){
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            tmp[k] = (*this)[k];
        for(int k = lo; k <= hi; k++)
            if(i > mid)
                (*this)[k] = tmp[j++];
            else if(j > hi)
                (*this)[k] = tmp[i++];
            else if(tmp[i] > tmp[j])
                (*this)[k] = tmp[j++];
            else
                (*this)[k] = tmp[i++];
    }
    void insertSort(int lo, int hi){
        for(int i = lo + 1; i <= hi; i++)
            for(int j = i; j > lo && (*this)[j] < (*this)[j - 1]; j--)
                swap((*this)[j], (*this)[j - 1]);
    }


};

template <typename T> class MergeBUSort : public SortList<T>{
private:
    vector<T> tmp;
public:
    MergeBUSort(vector<T> _vT) : SortList<T>(_vT), tmp(SortList<T>::vT.size()) {}
    void sort(){
        SortList<T>::sortStart();
        int N = SortList<T>::vT.size();
        for(int step = 1; step < N; step *= 2)
            for(int lo = 0; lo < N - step; lo += step * 2)
                merge(lo, lo + step - 1, min(lo + 2 * step, N) - 1);
        SortList<T>::sortStop();
    }
    void merge(int lo, int mid, int hi){
        int i = lo, j = mid + 1;
        for(int k = lo; k <= hi; k++)
            tmp[k] = (*this)[k];
        for(int k = lo; k <= hi; k++)
            if(i > mid)
                (*this)[k] = tmp[j++];
            else if(j > hi)
                (*this)[k] = tmp[i++];
            else if(tmp[i] > tmp[j])
                (*this)[k] = tmp[j++];
            else
                (*this)[k] = tmp[i++];
    }
};

template <typename T> class QuickSort : public SortList<T>{
private:
    int insertLimit = 6;
public:
    QuickSort(vector<T> _vT) : SortList<T>(_vT) {}
    void sort(){
        SortList<T>::sortStart();
        _sort(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort(int lo, int hi){
        if(lo >= hi)
            return;
        int i = partition(lo, hi);
        _sort(lo, i - 1);
        _sort(i + 1, hi);
    }

    int partition(int lo, int hi){
        T pivot = (*this)[lo];
        while(lo < hi){
            while(lo < hi && (*this)[hi] >= pivot)
                hi--;
            (*this)[lo] = (*this)[hi];
            while(lo < hi && (*this)[lo] <= pivot)
                lo++;
            (*this)[hi] = (*this)[lo];
        }
        (*this)[lo] = pivot;
        return lo;
    }
    
    void sort3_3_1(){
        SortList<T>::sortStart();
        _sort3_3_1(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort3_3_1(int lo, int hi){
        if(lo >= hi)
            return;
        else if(hi - lo <= insertLimit){
            insertSort(lo, hi);
            return;
        }
        int i = partition(lo, hi);
        _sort(lo, i - 1);
        _sort(i + 1, hi);
    }
    void insertSort(int lo, int hi){
        for(int i = lo + 1; i <= hi; i++)
            for(int j = i; j > 0 && (*this)[j] < (*this)[j - 1]; j--)
                swap((*this)[j], (*this)[j - 1]);
    }

    void sort3_3_2(){
        SortList<T>::sortStart();
        _sort3_3_2(0, SortList<T>::vT.size() - 1);
        SortList<T>::sortStop();
    }
    void _sort3_3_2(int lo, int hi){
        if(lo >= hi)
            return;
        else if(hi - lo <= insertLimit){
            insertSort(lo, hi);
            return;
        }
        insertSort(lo, lo + 2);
        swap((*this)[lo], (*this)[lo + 1]);
        int j = partition(lo, hi);
        _sort3_3_2(lo, j - 1);
        _sort3_3_2(j + 1, hi); 
    }

};

int Combination(int m, int n){
    int ans = 1, tmp = m;
    while(tmp--)
        ans *= n--;
    while(m)
        ans /= m--;
    return ans;
}

vector<double> B_Distrivution(int n, double p){
    vector<double> ans;
    for(int i = 0; i < n; i++)
        ans.push_back(Combination(i, n) * pow(p, i) * pow(1 - p, n - i));
    return ans;
}

vector<int> randomInt(int N){
    uniform_int_distribution<int> randomIntList;
    default_random_engine randomIntEngine(clock());
    vector<int> ans;
    for(int i = 0; i < N; i++)
        ans.push_back(randomIntList(randomIntEngine));
    return ans;
}

vector<int> rangeInt(int lo, int hi){
    vector<int> ans;
    for(; lo <= hi; lo++)
        ans.push_back(lo);
    return ans;
}

vector<int> sameInt(int num, int time){
    vector<int> ans;
    for(int n = 0; n < time; n++)
        ans.push_back(num);
    return ans;
}

int main(){

    int num = 6;
    InsertSort<int> insert(randomInt(num));
    SelectionSort<int> selection(randomInt(num));
    BubbleSort<int> bubble(randomInt(num));
    MergeSort<int> merge(randomInt(num));
    MergeBUSort<int> mergeBU(randomInt(num));
    QuickSort<int> quick(randomInt(num));

    insert.printInt();
    insert.sort();
    insert.printInt();
    cout << '\n';

    merge.printInt();
    merge.sort();
    merge.printInt();
    cout << '\n';

    mergeBU.printInt();
    mergeBU.sort();
    mergeBU.printInt();
    cout << '\n';

    quick.printInt();
    quick.sort();
    quick.printInt();
    cout << '\n';

    selection.printInt();
    selection.sort();
    selection.printInt();
    cout << '\n';

    bubble.printInt();
    bubble.sort();
    bubble.printInt();
    cout << '\n';

    return 0;

}