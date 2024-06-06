#include <iostream>

bool isEven(int value) {
    return (value & 1) == 0;
}

int main(){
    int number = 8;

    if (isEven(number)){
        std::cout << "is even" << std::endl;
    } else {
        std::cout << "is odd" << std::endl;
    }
    
    return 0;
}