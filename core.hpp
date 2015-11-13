#include <iostream>
#include "define.hpp"

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(API(CORE), int, CORE_INT)

  API(CORE) int core_function();
  API(CORE) void test_core();
}
