#include <iostream>
#include "define.hpp"

#ifdef EXPORT_APP1
#undef  API
#define API API_EXPORT
#else
#undef  API
#define API API_IMPORT
#endif

namespace Kratos {

  KRATOS_DEFINE_VARIABLE(int, APP1_INT)

  API int app1_function();
  API void test_app1();
}
