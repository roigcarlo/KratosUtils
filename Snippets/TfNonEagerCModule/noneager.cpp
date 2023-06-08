#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Foo {
    public:
        static std::vector<double> add(std::vector<double> a) {
            for(std::size_t i = 0; i < a.size(); i++) {
                a[i] /= 2.0;
            }

            return a;
        }
};

PYBIND11_MODULE(NonEager, m) {

    py::class_<Foo>(m, "Foo")
        .def_static("Add", &Foo::add)
        ;
}
