#include <boost/python.hpp>

#include "mpiProxy.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(mpiProxy)
{
  class_<MpiProxy>("MpiProxy")
    .def("ImportantFunction", &MpiProxy::ImportantFunction)
  ;
}