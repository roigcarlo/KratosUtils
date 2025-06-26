#include <vector>
#include <ranges>
#include <iostream>

// Data
#include "data_types.hpp"

// Views
#include "tensor_view.hpp"

int main() {

    // This emulates data inside a container
    std::vector<Data::Array1D<double, 3>> myData(1000);

    // This is how we interact with the data container
    auto ctnr_view = myData | std::views::transform([](Data::Array1D<double, 3>& item) -> double& {return item[0];});

    // This is the minimalistic TensorView implementation that we use to collect and store data
    TensorView<int, decltype(ctnr_view)> tensorView{ctnr_view};

    // Collect data
    tensorView.CollectData();

    // Modify the data (and this is exposed to python as well so you can do whatever you want)
    for (auto& item : tensorView.GetData()) {
        item += 1;
    }

    // Store data back to the original container
    tensorView.StoreData();

    // Print the first 10 items to verify
    for (auto& item: myData | std::views::take(10)) {
        std::cout << item[0] << " ";
    }   

    return 0;

}