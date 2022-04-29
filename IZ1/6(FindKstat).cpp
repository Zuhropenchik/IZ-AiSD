#include <iostream>
using std::swap;
template <typename T>
class Cmp{
public:
    bool operator()(const T&l, const T&r){return l>r;}
};
template <typename T, class Compare = Cmp<T>>
int three_medians(const T *a, int l, int r, Compare cmp){
    int mid = (r+l-1)/2;
    if(cmp(a[l],a[mid])) {
        if (cmp(a[mid],a[r-1]))
            return mid;
        else
        if(cmp(a[r-1],a[l]))
            return l;
        else
            return r-1;
    } else {
        if (cmp(a[l], a[r-1]))
            return l;
        else
        if(cmp(a[r-1],a[mid]))
            return mid;
        else
            return r-1;
    }
}
template <typename T, class Compare = Cmp<T>>
int Partition(T *a, int l, int r, Compare cmp = Cmp<T>()){
    if(r-l<1)
        return l;
    if(r-l>1)
        swap(a[l], a[three_medians(a,l, r, cmp)]);
    T pivot = a[l];
    int j=r-1;
    int i=r-1;
    while (j > l) {
        while (j > l && cmp(pivot, a[j])) --j;
        if (j != l)
            swap(a[i--], a[j--]);
    }
    swap(a[i],a[l]);
    return i;
}
template <typename T, class Compare = Cmp<T>>
T FindKStat(T *a, int l, int r, int k, Compare cmp = Cmp<T>()){
    int pivotPos=0;
    while ((pivotPos = Partition(a, l, r, cmp)) != k) {
        if (pivotPos < k)
            l = pivotPos + 1;
        else
            r = pivotPos;
    }

    return a[pivotPos];
}
int main(){
    int n;
    std::cin >> n;
    int *a = new int[n];
    for(int i=0; i<n;i++) {
        std::cin >> a[i];
    }
    std::cout << FindKStat(a,0,n,n/10) << '\n';
    std::cout << FindKStat(a,0, n,n/2) << '\n';
    std::cout << FindKStat(a,0,n,9*n/10) << '\n';
    delete[] a;
    return 0;
}
