// This file defines things
#ifndef KRATOS_DEFINES
#define KRATOS_DEFINES
#define KRATOS_DEFINE_VARIABLE(type, name)      extern type name;
#define KRATOS_CREATE_VARIABLE(type, name, val) type name = val;
#define KRATOS_REGISTER_VARIABLE(var) // NOT USED HERE
#endif
