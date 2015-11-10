#include <iostream>
#include "define.hpp"

#ifdef EXPORT_APP1
  #define API __declspec(dllexport)
#else
  #define API __declspec(dllimport)
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, APP1_INT)

  API int app1_function();
  API void test_app1();
}
