#include <iostream>
#include <functional>
#include <unordered_map>

// Hash function to be able to simulate Kratos "Tables"
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

// This should look like a simplified Kratos `Properties` class
class Properties {

    // Types
    typedef std::string KeyType;
    typedef double      ValueType;

    // AccessorType
    typedef std::function<ValueType(std::string, Properties const *, std::string, std::string)> AccessorType;

    public:
        Properties() {}
        ~Properties() {}

        // This trick will work as long as the arguments of the lambdas stored in mAccessor are fixed and allows:
        // - To call `Get` with 1 argument when no accessor for that `name`
        // - To call `Get` with 1 argument when the lambda does not use the extra strings (but are there because you need to have a unique type)
        // - To call `Get` with N arguments.
        // TL;DR: It works as std::placeholder, but you can leave them empty.
        template<typename ...TArgs>
        double Get(const std::string & name, TArgs... args) {
            return this->_Get(name, args..., "", "");
        }

        const std::unordered_map<KeyType, double> & GetProperties() const {
            return mProperties;
        }

        void AddAccessor(KeyType name, AccessorType && accessor) {
            mAccessors[name] = accessor;
        }

    private:
        template<typename ...TArgs>
        double _Get(const std::string & name, const std::string & idx1, const std::string & idx2, TArgs... args) {
            auto value = mAccessors.find(name);
            if (value != mAccessors.end()) {
                return value->second(name, this, idx1, idx2);
            } else {
                return mProperties[name];
            }
        }

        // Note: `mProperties` simulates the Kratos DB, but could be whatever. `mAccessors` is inteded like it is).
        std::unordered_map<KeyType, AccessorType> mAccessors  = {};
        std::unordered_map<KeyType, double>       mProperties = {
            {"alpha", 1.0},
            {"beta",  2.0},
            {"gamma", 3.0},
            {"delta", 4.0}
        };
};

class TableAccessor {
    // Types
    typedef std::string KeyType;
    typedef double      ValueType;

    // AccessorType
    typedef std::function<ValueType(std::string, Properties const *, std::string, std::string)> AccessorType;

    public:

        AccessorType mAccesor = [this](std::string name, Properties const * my_properties, std::string idx1, std::string idx2) -> double {
            return this->mValues.at(
                std::pair<double, double>(my_properties->GetProperties().at(idx1), my_properties->GetProperties().at(idx2))
            );
        };

    private:

        std::unordered_map<std::pair<double, double>, double, pair_hash> mValues = {
            {std::pair<double, double>(1.0, 1.0), 10.0},
            {std::pair<double, double>(1.0, 2.0), 20.0},
            {std::pair<double, double>(1.0, 3.0), 30.0},
            {std::pair<double, double>(2.0, 1.0), 40.0},
            {std::pair<double, double>(2.0, 2.0), 50.0},
            {std::pair<double, double>(2.0, 3.0), 60.0},
            {std::pair<double, double>(3.0, 1.0), 70.0},
            {std::pair<double, double>(3.0, 2.0), 80.0},
            {std::pair<double, double>(3.0, 3.0), 90.0}
        };
};

class VarTbAccessor {
    // Types
    typedef std::string KeyType;
    typedef double      ValueType;

    // AccessorType
    typedef std::function<ValueType(std::string, Properties const *, std::string, std::string)> AccessorType;

    public:

        AccessorType mAccesor = [this](std::string name, Properties const * my_properties, std::string idx1, std::string idx2) -> double {
            return this->mValues.at(
                std::pair(my_properties->GetProperties().at(name), my_properties->GetProperties().at(mTableLookup))
            );
        };

        void Update(std::string name) {
            mTableLookup = name;
        };

    private:

        std::string mTableLookup = "alpha";
        std::unordered_map<std::pair<double, double>, double, pair_hash> mValues = {
            {std::pair<double, double>(1.0, 1.0), 10.0},
            {std::pair<double, double>(1.0, 2.0), 20.0},
            {std::pair<double, double>(1.0, 3.0), 30.0},
            {std::pair<double, double>(2.0, 1.0), 40.0},
            {std::pair<double, double>(2.0, 2.0), 50.0},
            {std::pair<double, double>(2.0, 3.0), 60.0},
            {std::pair<double, double>(3.0, 1.0), 70.0},
            {std::pair<double, double>(3.0, 2.0), 80.0},
            {std::pair<double, double>(3.0, 3.0), 90.0}
        };
};

class DirctAccessor {
    // Types
    typedef std::string KeyType;
    typedef double      ValueType;

    // AccessorType
    typedef std::function<ValueType(std::string, Properties const *, std::string, std::string)> AccessorType;

    public:

        AccessorType mAccesor = [this](std::string name, Properties const * my_properties, std::string idx1="None", std::string idx2="None") -> double {
            return my_properties->GetProperties().at(name) + 0.1;
        };

    private:
};

int main() {
    auto my_properties = Properties();

    // Imagine this is python ----------------- //
    auto table_accessor = TableAccessor();
    auto vartb_accessor = VarTbAccessor();
    auto dirct_accessor = DirctAccessor();
    // Stop imagining --------------------------//

    // At this point I will have that object, either from python or either from another place.
    
    // Register the accessors
    my_properties.AddAccessor("alpha", std::move(table_accessor.mAccesor));
    my_properties.AddAccessor("beta",  std::move(vartb_accessor.mAccesor));
    my_properties.AddAccessor("gamma", std::move(dirct_accessor.mAccesor));

    // Accessing a variable means getting a value from table (x,y) = z
    std::cout << "table_accessor: " << my_properties.Get("alpha", "alpha", "alpha") << std::endl;   // 10.0
    std::cout << "table_accessor: " << my_properties.Get("alpha", "alpha", "gamma") << std::endl;   // 30.0
    std::cout << "table_accessor: " << my_properties.Get("alpha", "gamma", "gamma") << std::endl;   // 90.0

    // Accessing a variable means getting a value from table (x, [variable]) = z 
    std::cout << "Beta : " << my_properties.Get("beta") << std::endl;                               //  40.0

    vartb_accessor.Update("beta");
    std::cout << "Beta : " << my_properties.Get("beta") << std::endl;                               //  50.0

    vartb_accessor.Update("gamma");
    std::cout << "Beta : " << my_properties.Get("beta") << std::endl;                               //  60.0

    // Accessing a variable means executing an operation
    std::cout << "Gamma: " << my_properties.Get("gamma") << std::endl;                              //   3.1

    // Acess without accesor (normal)
    std::cout << "Delta: " << my_properties.Get("delta") << std::endl;                              //   4.0

    // Acess without accesor (normal, no overhead)
    std::cout << "Delta: " << my_properties.Get("delta") << std::endl;                              //   4.0
}