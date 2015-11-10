// This file is the main application that uses DLL
#include "core.hpp"

namespace Kratos {

  KRATOS_CREATE_VARIABLE(int, CORE_INT, 0)

  int core_function() {
    return CORE_INT;
  }

  void test_core() {
    std::cout << "CORE: I can execute myself" << std::endl;
    std::cout << "CORE: I can access own variables:\t" << CORE_INT << std::endl;
    std::cout << "CORE: I can access own functions:\t" << core_function() << std::endl;
  }

}
