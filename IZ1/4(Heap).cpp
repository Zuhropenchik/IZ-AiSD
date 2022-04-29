#include <iostream>

class process {
public:
    process() {
        t = 0;
        P = 0;
        T = 0;
    }

    process(int Pt, int Tt) {
        P = Pt;
        T = Tt;
        t = 0;
    }
    bool operator<(const process sec) const{
        int f = priority();
        int s = sec.priority();
        if (f <= s)
            return true;
        else
            return false;
    }

    int priority() const {
        return (t + 1) * P;
    }

    bool isAlive() const{
        if (t >= T)
            return false;
        else
            return true;
    }

    void get() {
        t += P;
    }

private:
    int P;
    int t;
    int T;
};


struct ProcessCmp{
    bool operator() (const process& l, const process& r){
        return l < r;
    }
};

template<class T, class Compare>
class Heap {
public:
    Heap(Compare _cmp) {
        buffer = new T;
        size = 0;
        buffer_size = 1;
        cmp = _cmp;
    }
    ~Heap(){
        delete[] buffer;
    };

    void add(const T& elem){
        if(size + 1 >= buffer_size){
            int new_buffer_size = buffer_size * 2;
            T* temp = new T[new_buffer_size];
            for (size_t i = 0; i < size; ++i) {
                temp[i] = buffer[i];
            }
            delete[] buffer;
            buffer = temp;
            buffer_size = new_buffer_size;
        }
        buffer[size++] = elem;
        sift_up(size - 1);
    }

    T pop(){
        if(is_empty()){
            return process(-1, 0);
        }

        T temp = buffer[0];
        buffer[0] = buffer[size-1];
        size--;
        sift_down(0);
        return temp;
    }

    bool is_empty() const{
        return size == 0;
    };
private:
    Compare cmp;

    T* buffer;
    size_t size;
    size_t buffer_size;

    void sift_down(size_t index){
        size_t left = index * 2 + 1;
        size_t right = index * 2 + 2;

        size_t min = index;
        if (left < size && cmp(buffer[left], buffer[min]))
            min = left;
        if (right < size && cmp(buffer[right], buffer[min]))
            min = right;

        if (min != index){
            T temp = buffer[index];
            buffer[index] = buffer[min];
            buffer[min] = temp;
            sift_down(min);
        }
    };

    void sift_up(size_t index){
        while(index > 0) {
            size_t head = (index - 1) / 2;
            if (buffer[index] < buffer[head])
                return;
            std::swap(buffer[head], buffer[index]);
            index = head;
        }
    }
};

int Process_Scheduler(Heap<process, ProcessCmp> &HP) {
    int switching = 0;
    process temp;
    while (!HP.is_empty()) {
        temp = HP.pop();
        temp.get();
        if (temp.isAlive()) {
            HP.add(temp);
        }
        switching++;
    }
    return switching;
}

int main() {
    ProcessCmp func;
    Heap<process, ProcessCmp> HP(func);
    int n;
    std::cin >> n;
    for(int i=0; i<n; i++) {
        int P, T;
        std::cin >> P >> T;
        HP.add(process(P,T));
    }
    std::cout << Process_Scheduler(HP);
    return 0;
}
