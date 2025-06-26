#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

class Dof {
    public:
        int mValue;

        Dof(int v) : mValue(v) {};
        int GetValue() {return mValue;}
        void SetValue(int v) {mValue = v;}
};

class Container {
    public:
        static std::vector<Dof *> mDofs;
};

std::vector<Dof *> Container::mDofs = std::vector<Dof *>({
    new Dof(1), new Dof(2), new Dof(3) 
});

PYBIND11_MODULE(BindModule, m) {
    pybind11::class_<Dof>(m, "Dof")
        .def("GetValue", &Dof::GetValue)
        .def("SetValue", &Dof::SetValue)
        .def_static("ModifyVaList", [](){
            for (auto& item: Container::mDofs) {
                item->SetValue(item->GetValue()+1);
            } 
        })
        .def_static("GetValueList", [](){
            std::vector<Dof *> tmp;

            for (auto& item: Container::mDofs) {
                tmp.push_back(item);
            }

            return tmp;
        });
}
