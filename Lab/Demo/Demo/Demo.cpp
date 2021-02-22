#include <iostream>
#include "Vector.h"

int main()
{
    Vector v1(3, 4);
    Vector v2(-3, -4);
    Vector v3 = v1.sum(v2);

    std::cout << "R vector (3, 4): " << v1.r().getValue() << "\n";
    std::cout << "fi vector (-3, -4): " << v2.fi().getValue() << "\n";
    std::cout << "R vector (-3, -4): " << v2.r().getValue() << "\n";
    std::cout << "R of sum vectors (3, 4) (-3, -4): " << v3.r().getValue() << "\n";

    std::cout << "Nums 0, 1: " << zero.getValue() << " " << one.getValue() << "\n";
}
