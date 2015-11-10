#ifndef KRATOS_DEFINES
#define KRATOS_DEFINES

#ifdef _WIN32
  #define API_EXPORT __declspec(dllexport)
  #define API_IMPORT __declspec(dllimport)
#else
  #define API_EXPORT __attribute__((visibility("default")))
  #define API_IMPORT __attribute__((visibility("default")))
#endif

#define KRATOS_DEFINE_VARIABLE(type, name)      API extern type name;

#define KRATOS_CREATE_VARIABLE(type, name, val) API type name = val;
#define KRATOS_REGISTER_VARIABLE(var) // NOT USED HERE

#endif
