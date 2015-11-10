#include "core.hpp"
#include "app1.hpp"
#include "app2.hpp"

using namespace Kratos;

int main() {
  std::cout << "All test" << std::endl;
  std::cout << "------------------------" << std::endl;
  test_core();
  std::cout << "------------------------" << std::endl;
  test_app1();
  std::cout << "------------------------" << std::endl;
  test_app2();
  std::cout << "------------------------" << std::endl;
}
