#include <iostream>
void input_array(long long * &a,int& n){
    std::cin >> n;
    a = new long long[n];
    for(int i=0; i<n; i++)
        std::cin >> a[i];
}
void output_array(long long * a,int n){
    for(int i=0; i<n; i++)
        std::cout << a[i] << " ";
}
void Copy(const long long * a, long long * copy, int n){
    for(int i=0; i<n;i++)
        copy[i] = a[i];
}
void Count_Sort(long long *a, long long * copy, int n, int r){
    int * temp = new int[256];
    unsigned char * t;
    for(int i=0; i<256;i++)
        temp[i] = 0;
    for(int i=0; i<n;i++){
        t = (unsigned char*)(&a[i])+r;
        temp[(int)*t]++;
    }
    for(int i=0; i<256; i++){
        if(i==0)
            temp[i]--;
        else
            temp[i] = temp[i]+temp[i-1];
    }
    for(int i=n-1; i>=0; i--){
        t = (unsigned char*)(&a[i])+r;
        copy[temp[(int)*t]] = a[i];
        temp[(int)*t]--;
    }
    Copy(copy, a, n);
    delete[] temp;
}
void Radix_Sort(long long* a, long long * copy, int n) {
    for(int i=0;i<sizeof(long long); i++)
        Count_Sort(a,copy,n,i);
}

int main() {
    long long *a, *copy;
    int n;
    input_array(a,n);
    copy = new long long[n];
    Copy(a, copy, n);
    Radix_Sort(a, copy, n);
    output_array(a,n);
    delete[] a;
    delete[] copy;
    return 0;
}
