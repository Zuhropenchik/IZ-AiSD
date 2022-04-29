#include <iostream>
unsigned short bit_num(unsigned int value){
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
    return num;
}
int main() {
    unsigned int value;
    std::cin >> value;
    std::cout << bit_num(value);
    return 0;
}
