#include<iostream>
#include"BTree.h"
struct Int_Compare {
    bool operator()(const int &f, const int &s) {
        return f >= s;
    }
};
/*2 10
0 1 2 3 4 5 6 7 8 9*/

//3
//1 5 7
//0 2 4 6 8 9


/*4 10
0 1 2 3 4 5 6 7 8 9*/

//3
//0 1 2 4 5 6 7 8 9
int main(){
    Int_Compare cmp;
    int n,m, temp;
    std::cin >> n >> m;
    BTree<int, Int_Compare> tree(cmp, n);
    for(int i=0; i<m; ++i){
        std::cin >> temp;
        tree.Add(temp);
    }
    return 0;
}
