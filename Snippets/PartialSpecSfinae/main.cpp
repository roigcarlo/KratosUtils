#include "condition.h"
#include "wall_law.h"

int main() {
    auto m2d2nWL  = MyCondition<2, WallLaw>();
    auto m3d3nWL  = MyCondition<3, WallLaw>();
    auto m2d2nWLD = MyCondition<2, WallLawDerived>();
    auto m3d3nWLD = MyCondition<3, WallLawDerived>();

    auto m2d2nWL_r  = m2d2nWL.Calculate(0.0);
    auto m3d3nWL_r  = m3d3nWL.Calculate(0.0);
    auto m2d2nWLD_r = m2d2nWLD.Calculate(0.0);
    auto m3d3nWLD_r = m3d3nWLD.Calculate(0.0);

    std::cout << "(2D2N-WL ) " << typeid(m2d2nWL_r).name()  << " " << m2d2nWL_r  << std::endl;
    std::cout << "(3D3N-WL ) " << typeid(m3d3nWL_r).name()  << " " << m3d3nWL_r  << std::endl;
    std::cout << "(2D2N-WLD) " << typeid(m2d2nWLD_r).name() << " " << m2d2nWLD_r << std::endl;
    std::cout << "(3D3N-WLD) " << typeid(m3d3nWLD_r).name() << " " << m3d3nWLD_r << std::endl;

    return 0;
}