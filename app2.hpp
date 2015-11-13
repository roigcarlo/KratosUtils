#include <iostream>
#include "define.hpp"

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(API(APP2), int, APP2_INT)

  API(APP2) int app2_function();
  API(APP2) void test_app2();
}
