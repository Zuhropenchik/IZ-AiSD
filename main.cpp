#include <iostream>
void input_array(int * &a,int& n){
    std::cin >> n;
    a = new int[n];
    for(int i=0; i<n; i++)
        std::cin >> a[i];
}
int binary_search(int * a,int l,int r, int value){
    int i = (l+r)/2;
    while(r-l>1){
        if(value>a[i])
            l = i;
        else if(value<a[i])
            r = i;
        else
            return i;
        i = (l+r)/2;
    }
    if(a[r]-value < value - a[l])
        return i+1;
    return i;
}
int log_search(int *a,int n, int value){
    if(a[0] == value)
        return 0;
    int r = 1;
    while(r<=n-1 && a[r]<=value )
        r*=2;
    if(r>n-1)
        r = n-1;
    return binary_search(a,r/2,r,value);
}
int main() {
    int *a , *b;
    int n, m;
    input_array(a,n);
    input_array(b,m);
    for(int i=0; i<m; i++) {
        std::cout << log_search(a,n,b[i]) << " ";
    }
    delete[] a;
    delete[] b;
    return 0;
}