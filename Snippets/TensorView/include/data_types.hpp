#pragma once

namespace Data {
    
template<typename T, int Dim>
class Array1D {
    public:
        std::array<T, Dim> data;

        Array1D() {
            data.fill(0);
            for (std::size_t i = 0; i < Dim; i++) {
                data[i] = static_cast<T>((i+1) * 10);
            }
        }

        T& operator[](size_t index) {
            return data[index];
        }
};

}