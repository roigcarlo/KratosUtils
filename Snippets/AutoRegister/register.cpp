#include <mutex>
#include <string>
#include <memory>
#include <iostream>
#include <functional>
#include <unordered_map>

std::once_flag flag_once;

class RegistryValueItemHolderBase {

public:

    RegistryValueItemHolderBase(void * value) : mpInstancePtr(value) {};

    template<typename TDataType> TDataType const& GetValue() const
    {
        return *static_cast<const TDataType*>(mpInstancePtr);
    }

    void * mpInstancePtr;
};

template<class TDispatcherType, class TValueType>
class RegistryValueItemHolder : public RegistryValueItemHolderBase {

public:

    RegistryValueItemHolder(TDispatcherType disparcher) : RegistryValueItemHolderBase(nullptr), mDisparcher(disparcher) {
        if(mpInstancePtr == nullptr) {
            mpValue = mDisparcher();
            mpInstancePtr = &*mpValue;
        }
    };

    std::shared_ptr<TValueType> mpValue;
    TDispatcherType mDisparcher;
};

class RegistryItem {

    using SubRegistryItemType = std::unordered_map<std::string, std::shared_ptr<RegistryItem>>;

public:

    RegistryItem() = delete;

    RegistryItem(std::string Name) : mName(Name), mpDispatcher(nullptr){}

    template<class TDispatcherType, class TValueType>
    RegistryItem(std::string Name, TDispatcherType Dispatcher, TValueType* Value) : mName(Name) {
        mpDispatcher = std::make_shared<RegistryValueItemHolder<TDispatcherType, TValueType>>(Dispatcher);
    }

    /// Destructor.
    virtual ~RegistryItem(){}

    template< typename TItemType, class TDispatcherType, class TValueType>
    RegistryItem& AddItem(std::string const& ItemName, TDispatcherType Dispatcher, TValueType* Value)
    {
        auto insert_result = mSubRegistryItem.emplace(
            std::make_pair(
                ItemName,
                std::make_unique<TItemType>(ItemName, Dispatcher, Value)
            )
        );

        return *insert_result.first->second;
    }

    RegistryItem& GetItem(std::string const& rItemName)
    {
        auto iterator = mSubRegistryItem.find(rItemName);
        return *(iterator->second);
    }

    template<typename TDataType> TDataType const& GetValue() const
    {
        return mpDispatcher->GetValue<TDataType>();
    }

    std::string mName;
    std::shared_ptr<RegistryValueItemHolderBase> mpDispatcher;
    
    SubRegistryItemType mSubRegistryItem;
};

template<class TValueType>
class RegistryValueItem : public RegistryItem {

public:

    RegistryValueItem() = delete;

    template<class TDispatcherType>
    RegistryValueItem(
        std::string const& Name,
        TDispatcherType Dispatcher,
        TValueType* Value)
        : RegistryItem(Name, Dispatcher, Value)
    {}

    virtual ~RegistryValueItem()
    {
        // I think there is no longer need to delete anything
        // value will get deleted once mpValue gets no refereces (registry destruction)
    }
};

class Registry {

public:

    static RegistryItem& GetRootRegistryItem()
    {
        if (!mspRootRegistryItem) {
            std::call_once(flag_once, [](){
                static RegistryItem root_item("Registry");
                mspRootRegistryItem = &root_item;
            });
        }

        return *mspRootRegistryItem;
    }

    template< typename TItemType, class TValueType, class TDispatcherType>
    static RegistryItem& AddItem(
        std::string const& rItemFullName,
        TDispatcherType Dispatcher,
        TValueType* Value = nullptr)
    {
        RegistryItem* p_current_item = &GetRootRegistryItem();
        p_current_item = &p_current_item->AddItem<TItemType>(rItemFullName, Dispatcher, Value);

        return *p_current_item;
    }

    static RegistryItem& GetItem(std::string const& rItemFullName)
    {
        RegistryItem* p_current_item = &GetRootRegistryItem();
        p_current_item = &p_current_item->GetItem(rItemFullName);

        return *p_current_item;
    }

    static RegistryItem* mspRootRegistryItem;
};

RegistryItem* Registry::mspRootRegistryItem = nullptr;

#define CLASS_REGISTER_DEFINITION(NAME, ...)                                                        \
    static inline RegistryItem msRegistryItem = Registry::AddItem<RegistryValueItem<NAME>, NAME>(   \
        #NAME, [](){                                                                                \
            return std::make_shared<NAME>(__VA_ARGS__);                                             \
        }                                                                                           \
    );

class SampleProcess {

public:

    // Incomplete types (aka the consturctor with the class name we are trying to define) cannot be used
    // here, not even as a return type of the lambda.
    // 1 - Using a shard_ptr<SampleProcess> solves the problem.
    // 2 - We cannot initialize even that pointer becuase the constructor is missing (we are still defining the class)
    // 3 - We can create a dispatcher that creates the object once is accessed for the first time (and use it a ***singleton***)
    CLASS_REGISTER_DEFINITION(SampleProcess)

    std::string Info() const {
        return "SamplePorcess!";
    };
};

std::ostream& operator<< (std::ostream &out, SampleProcess &sp) {
    out << "Hey, I am a: " << sp.Info() << std::endl;
    return out;
};

int main() {
    
    auto& value1 = Registry::GetItem("SampleProcess").GetValue<SampleProcess>();
    auto& value2 = Registry::GetItem("SampleProcess").GetValue<SampleProcess>();

    std::cout << "Hey, I've got a " << value1.Info() << " @: " << &value1 << std::endl;
    std::cout << "Hey, I've got a " << value2.Info() << " @: " << &value2 << std::endl;

    return 0;
}