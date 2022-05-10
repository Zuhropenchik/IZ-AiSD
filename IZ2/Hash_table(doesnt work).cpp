#include <iostream>
#include <vector>

using std::vector;
using std::string;

struct StringHasher{
    unsigned int operator() (const string&key){
        unsigned int hash = 0;
        for(int i=0;i<key.length();++i)
            hash = hash * 137 +  key[i];
        return hash;
    }
};
template<class T, class H>
class HashTable{
public:
    HashTable(int initSize, const H& _hasher);
    ~HashTable();
    bool Has(const T& key) const;
    bool Add(const T& key);
    bool Delete(const T& key);
    void growTable();
private:
    struct HashTableNode{
        T Key;
        HashTableNode* Next;
    };
    H hasher;
    vector<HashTableNode*> table;
    unsigned int keysCount;
};

template<class T, class H>
HashTable<T,H>::HashTable(int initSize, const H& _hasher):
hasher(_hasher),
table(initSize, nullptr),
keysCount(0){}

template<class T, class H>
HashTable<T,H>::~HashTable(){
    for(int i=0; i<table.size();++i){
        HashTableNode * node = table[i];
        while(node!=nullptr){
            HashTableNode * nextNode = node->Next;
            delete node;
            node= nextNode;
        }

    }
}

template<class T, class H>
bool HashTable<T,H>::Has(const T& key)const {}

template<class T, class H>
bool HashTable<T,H>::Add(const T& key){
    if(Has(key))
        return false;
    if(keysCount > 3 * table.size())
        growTable();
    int hash = hasher(key ) % table.size();
    HashTableNode* node = table[hash];
    while()
}

template<class T, class H>
bool HashTable<T,H>::Delete(const T& key){}
template<class T,class H>
void HashTable<T,H>::growTable(){}
int main(){

}
