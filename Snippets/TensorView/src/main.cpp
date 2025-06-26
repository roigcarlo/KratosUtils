#include <vector>
#include <ranges>
#include <iostream>

// Data
#include "data_types.hpp"

// Views
#include "tensor_view.hpp"

int main() {

    std::vector<Data::Array1D<double, 3>> myData(1000);

    auto ctnr_view = myData | std::views::transform([](Data::Array1D<double, 3>& item) -> double& {return item[0];});

    TensorView<int, decltype(ctnr_view)> tensorView{ctnr_view};

    tensorView.CollectData();

    for (auto& item : tensorView.GetData()) {
        item += 1;
    }

    tensorView.StoreData();

    for (auto& item: myData | std::views::take(10)) {
        std::cout << item[0] << " ";
    }   

    return 0;

}