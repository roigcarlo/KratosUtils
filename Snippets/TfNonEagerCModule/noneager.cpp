#include <pybind11/pybind11.h>

namespace py = pybind11;

class Foo {
    public:
        static double add(double a) {
            return a + 1.0;
        }
};

PYBIND11_MODULE(NonEager, m) {

    py::class_<Foo>(m, "Foo")
        .def_static("Add", &Foo::add)
        ;
}
