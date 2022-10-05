#include <map>
#include <any>
#include <list>
#include <tuple>
#include <memory>
#include <variant>
#include <iostream>
#include <functional>
 
class ArgHolder : public std::enable_shared_from_this<ArgHolder>{
  public:
    ArgHolder() {}
    
    template<class TArgType>
    TArgType Get() {
        // std::cout << " - Get With Typeid: " << typeid(TArgType).name() << std::endl;
        // Im sure there is a way to do this in 1 line
        auto return_value = std::any_cast<TArgType>(mData.back()); mData.pop_back();
        return return_value;
    }
    
    template<class TThisType>
    std::shared_ptr<ArgHolder> Set(TThisType thisItem) {
        // std::cout << " - Set With Typeid (END): " << typeid(thisItem).name() << std::endl;
        mData.push_back(thisItem);
        return shared_from_this();
    }
    
    template<class TThisType, class... TArgType>
    std::shared_ptr<ArgHolder> Set(TThisType thisItem, TArgType... rest) {
        // std::cout << " - Set With Typeid (REC): " << typeid(thisItem).name() << std::endl;
        mData.push_back(thisItem);
        Set(rest...);
        return shared_from_this();
    }
    
    template<class TRtype, class... TArgType>
    std::shared_ptr<TRtype> Caller() {
        return std::make_shared<TRtype>(std::make_from_tuple<TRtype>(std::tuple<TArgType...>(this->Get<TArgType>()...)));
    }
    
    std::list<std::any> mData;
};

class Process {
  public:
    virtual void printInfo() {
        std::cout << "Base clase is Based" << std::endl; 
    }
};

// This represents the regular Model,Parameter constructor
class MyProcessStd : public Process {
  public:
    MyProcessStd(int a, int b)
    : mVarIntA(a), mVarIntB(b) {
        // std::cout << "Creating StdProcess..." << std::endl;
    }
    
    virtual void printInfo() {
        std::cout << "Std Process: " << mVarIntA << " " << mVarIntB << std::endl; 
    }
    
    int mVarIntA;
    int mVarIntB;
};

// This represents a random arg constructor
class MyProcessRnd : public Process {
  public:
    MyProcessRnd(std::string s, int a, int b) 
    : mVarStr(s), mVarIntA(a), mVarIntB(b) {
        // std::cout << "Creating RndProcess..." << std::endl;
    }
    
    virtual void printInfo() {
        std::cout << "Std Process: " << mVarStr << " " << mVarIntA << " " << mVarIntB << std::endl; 
    }
    
    std::string mVarStr;
    int mVarIntA;
    int mVarIntB;
};

std::map<std::string, std::function<std::shared_ptr<Process>(std::shared_ptr<ArgHolder>)>> gRegistry;

#define REGISTER_PROCESS(NAME, ITEM) gRegistry[NAME] = ITEM;
// Vanilla
// REGISTER_PROCESS("MyProcessStd", [](std::shared_ptr<ArgHolder> ph){return std::make_shared<MyProcessStd>( MyProcessStd(ph->Get<int>(),ph->Get<int>()) );})
// REGISTER_PROCESS("MyProcessRnd", [](std::shared_ptr<ArgHolder> ph){return std::make_shared<MyProcessRnd>( MyProcessRnd(ph->Get<std::string>(),ph->Get<int>(),ph->Get<int>()));})

#define REGISTER_PROCESS_V2(NAME, ...) gRegistry[NAME] = [](std::shared_ptr<ArgHolder> ph){return ph->Caller<__VA_ARGS__>();};

int main() {

    REGISTER_PROCESS_V2("MyProcessStd", MyProcessStd, int, int)
    REGISTER_PROCESS_V2("MyProcessRnd", MyProcessRnd, std::string, int, int)
    
    auto std_parameters = std::make_shared<ArgHolder>()->Set(1,2);
    auto rnd_parameters = std::make_shared<ArgHolder>()->Set<std::string, int, int>("PepoBorpaSpin",1,2);
    
    auto process_std = gRegistry.at("MyProcessStd")(std_parameters);
    auto process_rnd = gRegistry.at("MyProcessRnd")(rnd_parameters);
    
    process_std->printInfo();
    process_rnd->printInfo();
    
    return 0;
}
