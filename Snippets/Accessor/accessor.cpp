#include <iostream>
#include <functional>
#include <unordered_map>

class Properties {

    // Using the assumtion that this won't change between accessors (as in the discussion)
    typedef std::function<double(std::string, Properties *)> AccessorType;

    public:
        Properties() {}
        ~Properties() {}

        template<typename ...TArgs>
        double Get(std::string name, TArgs... args) {
            auto value = mAccessors.find(name);
            if (value != mAccessors.end()) {
                return value->second(name, this);
            } else {
                return mProperties[name];
            }
        }

        void AddAccessor(std::string name, AccessorType && accessor) {
            mAccessors[name] = accessor;
        }

    // This should be private
    // private:
        std::unordered_map<std::string, AccessorType> mAccessors  = {};
        std::unordered_map<std::string, double>       mProperties = {
            {"alpha", 1.0},
            {"beta",  2.0},
            {"gamma", 3.0}
        };
};

int main() {
    auto my_properties = Properties();
    
    my_properties.AddAccessor("alpha", [](std::string name, Properties * my_properties) -> double {
        return my_properties->mProperties[name] + 0.1;
    });

    my_properties.AddAccessor("gamma", [](std::string name, Properties * my_properties) -> double {
        return 4.0;
    });

    std::cout << "Alpha: " << my_properties.Get("alpha") << std::endl;
    std::cout << "Beta : " << my_properties.Get("beta")  << std::endl;
    std::cout << "Gamma: " << my_properties.Get("gamma") << std::endl;
}