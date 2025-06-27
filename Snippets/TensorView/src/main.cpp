#include <vector>
#include <iostream>

#include <range/v3/view.hpp>

// Data
#include "data_types.hpp"

// Views
#include "tensor_view.hpp"

using CntrDataType = Data::Array1D<double, 3>;
using CntrType     = std::vector<CntrDataType>;
using DataViewType = double;
using IndexType    = std::size_t;

void operation_a(std::shared_ptr<DataView<DataViewType>> pDataView) {
  // Collect data
    pDataView->CollectData();

    // Modify the data (and this is exposed to python as well so you can do whatever you want)
    for (auto& item : pDataView->GetData()) {
        item += 1.0;
    }

    // Store data back to the original container
    pDataView->StoreData();
}

void operation_b(std::shared_ptr<DataView<DataViewType>> pDataView) {
    // Collect data
    pDataView->CollectData();

    // Modify the data (and this is exposed to python as well so you can do whatever you want)
    for (auto& item : pDataView->GetData()) {
        item += 2.0;
    }

    // Store data back to the original container
    pDataView->StoreData();
}

template<class TContainerView>
void context_emulator(TContainerView& cntr_view) {
    // Create a new containe view and assign a data accessor:
    // 0:               is the index accessor (e.g. 0 for the first item in the Array3D, VELOCITY for a node, etc... )
    // lambda function: is used to access the data inside the container as the user wishes.
    auto cntr_view_x = cntr_view->template FromThisView<DataViewType>()->CreateDataView(0, [](CntrDataType& item, IndexType index) -> DataViewType& {
        return item[index];
    });

    // Create a new containe view and assign a data accessor:
    // 1:               is the index accessor (e.g. 0 for the first item in the Array3D, VELOCITY for a node, etc... )
    // lambda function: is used to access the data inside the container as the user wishes.
    auto cntr_view_y = cntr_view->template FromThisView<DataViewType>()->CreateDataView(1, [](CntrDataType& item, IndexType index) -> DataViewType& {
        return item[index];
    });

    operation_a(cntr_view_x->GetDataView());
    operation_b(cntr_view_y->GetDataView());
}

int main() {

    // This emulates data inside a container
    CntrType myData(1000);

    // Create a container view over the container. This is a dummy/root container, but it could be used directly.
    auto cntr_view = std::make_shared<ContainerView<CntrType, DataViewType>>(myData);

    // Emulate some usage
    context_emulator(cntr_view);

    // Print the first 10 items to verify
    for (auto& item: myData | ranges::views::take(10)) {
        std::cout <<"(" << item[0] << "," << item[1] << ")" << std::endl;
    }   

    return 0;

}