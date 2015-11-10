#include <iostream>
#include "define.hpp"

#ifdef EXPORT_CORE
#undef  API
#define API API_EXPORT
#else
#undef  API
#define API API_IMPORT
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, CORE_INT)

  API int core_function();
  API void test_core();
}
