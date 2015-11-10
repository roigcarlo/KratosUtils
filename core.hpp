#include <iostream>
#include "define.hpp"

#ifdef EXPORT_CORE
  #pragma message("Exporting symbols for Core")
  #define API __declspec(dllexport)
#else
  #pragma message("NOT Exporting symbols for Core")
  #define API __declspec(dllimport)
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, CORE_INT)

  API int core_function();
  API void test_core();
}
