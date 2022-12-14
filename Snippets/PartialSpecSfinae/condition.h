#include <iostream>
#include <type_traits>

template<int A, class T>
class MyCondition {
public:
    auto Calculate(double rValue) {
        if constexpr (A == 2) {
            return Calculate_2D2M(rValue);
        } else {
            return Calculate_3D3N(rValue);
        }
    };

    double Calculate_2D2M(double rValue) {
        rValue += A;
        T::Apply(rValue);
        return rValue;
    };

    int Calculate_3D3N(double rValue) {
        rValue += A;
        T::Apply(rValue);
        return rValue;
    };
};