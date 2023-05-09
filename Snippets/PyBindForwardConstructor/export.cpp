#include <vector>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class AccessorBase {
    public:
        AccessorBase() 
        {
            std::cout << "Base Created" << std::endl;
        }

        virtual void GetProps() {
            std::cout << "I am Base accessor and my properties are:" << std::endl;
        }
};

class AccessorDerived : public AccessorBase {
    public:
        AccessorDerived(std::string name, int a, int b) 
            : AccessorBase()
            , mName(name)
            , mA(a)
            , mB(b) 
        {
            std::cout << "Derived Created" << std::endl;
        } 

        virtual void GetProps() {
            std::cout << "I am Derived accessor and my properties are:" << std::endl;
            std::cout << "\t mName: " << mName << std::endl; 
            std::cout << "\t mA:    " << mA    << std::endl; 
            std::cout << "\t mB:    " << mB    << std::endl; 
        }

    private:
        std::string mName;
        int mA;
        int mB;
};

class Properties {
    public:
        using TCreator = std::function<std::unique_ptr<AccessorBase>()>;

        AccessorBase * SetAccesor(const TCreator && accessorCreator) {
            mpAccessor = accessorCreator();
            return &*mpAccessor;
        }

        void GetProps() {
            mpAccessor->GetProps();
        }

    private:
        std::unique_ptr<AccessorBase> mpAccessor;
};

PYBIND11_MAKE_OPAQUE(std::unique_ptr<AccessorBase>);
PYBIND11_MAKE_OPAQUE(std::unique_ptr<AccessorDerived>);

PYBIND11_MODULE(ExportAccessor, m) {

    py::class_<AccessorBase>(m, "Accessor")
        .def("GetProps", &AccessorBase::GetProps)
        ;

    py::class_<std::unique_ptr<AccessorBase>>(m, "Unique_ptr_AccessorBase_binding");

    py::class_<AccessorDerived, AccessorBase>(m, "AccessorDerived")
        .def("Creator", [](std::string name, int a, int b) {
            Properties::TCreator creator = [name, a, b]() -> std::unique_ptr<AccessorBase> {
                return std::move(std::unique_ptr<AccessorBase>(new AccessorDerived(name, a, b)));
            };

            return creator;
        })
        ;

    py::class_<Properties>(m, "Properties")
        .def(py::init<>())
        .def("Set", &Properties::SetAccesor, py::return_value_policy::reference)
        .def("GetProps", &Properties::GetProps)
        ;
}
