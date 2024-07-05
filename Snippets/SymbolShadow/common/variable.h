#pragma once

#include <iostream>
#include <string>

class DynamicLoad {
  public:
    DynamicLoad() {
        std::cout << "DynamicLoad constructor" << std::endl;
    }

    ~DynamicLoad() {
        std::cout << "DynamicLoad destructor" << std::endl;
    }
};

class Variable {
  public:
    Variable(int id) {
        mId = id;
        mDynamicLoad = new DynamicLoad();
    }

    ~Variable() {
        std::cout << "Attempting to destroy variable with id: " << mId  << " and ptr pointing to " << mDynamicLoad << std::endl;
        delete mDynamicLoad;
    }

    int mId;
    DynamicLoad * mDynamicLoad;
};   