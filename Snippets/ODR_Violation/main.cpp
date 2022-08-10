#include <iostream>

#include "unit1/class_declaration.h"

int main() {
    auto a = MyClass<int>();
    auto b = MyClass<double>();

    std::cout << "Int:    " << a.printNumber() << std::endl;
    std::cout << "Double: " << b.printNumber() << std::endl;

    return 0;
}