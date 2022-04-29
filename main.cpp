#include <iostream>
int main() {
    unsigned int value;
    std::cin >> value;
    bool i = false;
    unsigned short num = 0;
    unsigned int temp;
    while(value>0) {
        temp = value & 1;
        if (!i && temp == 1)
            num++;
        if(i)
            i = false;
        else
            i = true;
        value = value >> 1;
    }
    std::cout << num;
    return 0;
}