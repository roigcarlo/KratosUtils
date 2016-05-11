#include <iostream>
#include "define.hpp"
#include "core.hpp"

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(API(APP1), int, APP1_INT)

  API(APP1) int app1_function();
  API(APP1) void test_app1();
}
