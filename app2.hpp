#include <iostream>
#include "define.hpp"

#ifdef EXPORT_APP2
#undef  API
#define API API_EXPORT
#else
#undef  API
#define API API_IMPORT
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, APP2_INT)

  API int app2_function();
  API void test_app2();
}
