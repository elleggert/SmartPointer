#include <iostream>
#include "SmartPointer.cpp"

int main() {
    //Creating some new smart pointers
    auto integer = new int;
    *integer = 1;
    SmartPointer<int> sm1(integer);
    auto sm2 = sm1;

    std::cout << sm1.getRefCount() << std::endl;

}
