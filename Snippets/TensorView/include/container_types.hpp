// namespace Containers {

//     template<typename T>
//     class PointerVector {
//         public:
//             std::vector<T*> data;

//             PointerVector() {}

//             void push_back(T* item) {
//                 data.push_back(item);
//             }

//             T* operator[](size_t index) {
//                 return data[index];
//             }

//             size_t size() const {
//                 return data.size();
//             }

//             void clear() {
//                 for (auto& item : data) {
//                     delete item;
//                 }
//                 data.clear();
//             }
//     };

// }