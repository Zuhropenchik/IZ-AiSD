#include <iostream>
#include <vector>

#define INIT_SIZE 8
using std::vector;
using std::string;

struct StringHasher {
    unsigned int operator()(const string &key) const {
        unsigned int hash = 0;
        for (auto i: key)
            hash = hash * 137 + i;
        return hash;
    }
};


template<class T, class H>
class HashTable {
private:
    struct Node {
        T key;
        bool isEmpty;
        bool isDeleted;

        Node() : isEmpty(true), isDeleted(false) {}
    };

    H hasher;
    vector<Node> table;
    unsigned int keysCount;
    unsigned int deletedCount;


    int find(const T &key, vector<Node> &curr_table);

    void growTable();


    unsigned int quadratic_probing(unsigned int prev, size_t i);

public:
    HashTable(int initSize, const H &_hasher);

    ~HashTable();

    bool Has(const T &key);

    bool Add(const T &key);

    bool Delete(const T &key);


};

template<class T, class H>
HashTable<T, H>::HashTable(int initSize, const H &_hasher):
        hasher(_hasher),
        table(initSize),
        keysCount(0),
        deletedCount(0) {}

template<class T, class H>
HashTable<T, H>::~HashTable() = default;

template<class T, class H>
bool HashTable<T, H>::Has(const T &key) {
    if (find(key, table) == -1)
        return false;
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Add(const T &key) {
    if (4 * (keysCount) > 3 * table.size() || 2 * deletedCount > table.size() - keysCount) { // нужно ли перехэшировать?
        growTable();
    }
    unsigned int hash = hasher(key) % table.size();
    size_t i = 0;
    while (!table[hash].isEmpty && i < table.size()) {
        if (!table[hash].isDeleted && table[hash].key == key) {
            return false;
        }
        ++i;
        hash = quadratic_probing(hash, i) % table.size();
    }
    if (i == table.size())
        return false;
    table[hash].isEmpty = false;
    table[hash].key = key;
    ++keysCount;
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T &key) {
    auto hash = (size_t) find(key, table);
    if (hash == -1)
        return false;
    table[hash].isDeleted = true;
    keysCount--;
    deletedCount++;
    return true;
}

template<class T, class H>
void HashTable<T, H>::growTable() {
    size_t newTableSize = table.size();
    if (4 * keysCount > 3 * table.size()) // если таблицу нужно расширять, увеличиваем новый размер, если нет, то
        newTableSize *= 2;               // перехэшируем со старым размером

    vector<Node> oldTable = std::move(table);
    vector<Node> newTable(newTableSize);
    keysCount = 0;
    deletedCount = 0;
    table = std::move(newTable);
    for (const auto &i: oldTable) {
        if (!i.isEmpty && !i.isDeleted) {
            Add(i.key);
        }
    }
}


template<class T, class H>
int HashTable<T, H>::find(const T &key, vector<Node> &curr_table) {
    unsigned int hash = hasher(key) % curr_table.size();
    size_t i = 0;
    while (!curr_table[hash].isEmpty && i < table.size()) {
        if (!curr_table[hash].isDeleted && curr_table[hash].key == key) {
            return (int) hash;
        }
        ++i;
        hash = quadratic_probing(hash, i) % curr_table.size();
    }
    return -1;
}

template<class T, class H>
unsigned int HashTable<T, H>::quadratic_probing(unsigned int prev, size_t i) {
    return prev + i;
}


int main() {
    const StringHasher hasher;
    HashTable<string, StringHasher> Hash_table(INIT_SIZE, hasher);
    char operation = '\0';
    string key;
    bool result = false;
    while (std::cin >> operation >> key) {
        switch (operation) {
            case '+':
                result = Hash_table.Add(key);
                break;
            case '-':
                result = Hash_table.Delete(key);
                break;
            case '?':
                result = Hash_table.Has(key);
                break;
            default:
                // Hash_table.print();
                break;
        }
        std::cout << ((result) ? "OK" : "FAIL") << std::endl;
    }
    return 0;
}
