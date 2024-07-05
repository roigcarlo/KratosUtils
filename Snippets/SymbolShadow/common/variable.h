#pragma once

#include <iostream>

class Variable {
  public:
    Variable(int id) {
        mId = id;
    }

    ~Variable() {
        std::cout << "Attempting to destroy variable with id: " << mId << std::endl;
    }

    int mId;
};   