#include "core.hpp"
#include "app1.hpp"
#include "app2.hpp"

namespace Kratos {

  KRATOS_CREATE_VARIABLE(int, APP2_INT, 2)

  int app2_function() {
    return APP2_INT;
  }

  void test_app2() {
    std::cout << "APP2: I can execute myself" << std::endl;
    std::cout << "APP2: I can access own variables:\t" << APP2_INT << std::endl;
    std::cout << "APP2: I can access own functions:\t" << app2_function() << std::endl;
    std::cout << "APP2: I can access shared variables:\t" << APP1_INT << std::endl;
    std::cout << "APP2: I can access shared functions:\t" << app1_function() << std::endl;
    std::cout << "APP2: I can access core variables:\t" << CORE_INT << std::endl;
    std::cout << "APP2: I can access core functions:\t" << core_function() << std::endl;
  }

}
