#include "core.hpp"
#include "app1.hpp"

namespace Kratos {

  KRATOS_CREATE_VARIABLE(int, APP1_INT, 1)

  int app1_function() {
    return APP1_INT;
  }

  void test_app1() {
    std::cout << "APP1: I can execute myself" << std::endl;
    std::cout << "APP1: I can access own variables:\t" << APP1_INT << std::endl;
    std::cout << "APP1: I can aceess own functions:\t" << app1_function() << std::endl;
    std::cout << "APP1: I can access core variables:\t" << CORE_INT << std::endl;
    std::cout << "APP1: I can aceess core functions:\t" << core_function() << std::endl;
  }

}
