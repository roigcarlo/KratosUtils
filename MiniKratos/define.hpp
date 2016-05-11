#ifndef KRATOS_DEFINES
#define KRATOS_DEFINES

#ifdef _WIN32
  #define API_EXPORT __declspec(dllexport)
  #define API_IMPORT __declspec(dllimport)
#else
  #define API_EXPORT __attribute__((visibility("default")))
  #define API_IMPORT __attribute__((visibility("default")))
#endif

// This fixes MSVC not expanding __VA_ARGS__ as defined in the C99 standard
#define EXPAND(A) A

// Random macro magic
#define API_CALL(x,T1,T2,T3,...) T3
#define API(...) EXPAND(API_CALL(,##__VA_ARGS__,API_EXPORT,API_IMPORT))

#define KRATOS_DEFINE_VARIABLE(api, type, name)      api extern type name;

#define KRATOS_CREATE_VARIABLE(api, type, name, val) api type name = val;
#define KRATOS_REGISTER_VARIABLE(var) // NOT USED HERE

#endif
