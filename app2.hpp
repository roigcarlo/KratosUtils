#include <iostream>
#include "define.hpp"

#ifdef EXPORT_APP2
  #define API __declspec(dllexport)
#else
  #define API __declspec(dllimport)
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, APP2_INT)

  API int app2_function();
  API void test_app2();
}
