#include <iostream>
#include "Vector.h"

int main()
{
    Number n1(100);
    Number n2 = createNumber(10);
    std::cout << "\nNumber1: " << n1.getValue() << ", Number2: " << n2.getValue() << "\n";
    std::cout << "+: " << (n1 + n2).getValue() << "\n";
    std::cout << "-: " << (n1 - n2).getValue() << "\n";
    std::cout << "*: " << (n1 * n2).getValue() << "\n";
    std::cout << "/: " << (n1 / n2).getValue() <<"\n";

    std::cout << "\n--------------------------\n";

    Vector v1(3, 4);
    Vector v2(-6, 8);
    Vector v3 = v1.sum(v2);

    std::cout << "\nVector1: (3, 4), Vector2: (-6, 8)\n";
    std::cout << "R vector1: " << v1.r().getValue() << "\n";
    std::cout << "fi vector1: " << v1.fi().getValue() << "\n";
    std::cout << "R vector2: " << v2.r().getValue() << "\n";
    std::cout << "fi vector2: " << v2.fi().getValue() << "\n";
    std::cout << "R sum vector1 and vector2: " << v1.sum(v2).r().getValue() << "\n";
    std::cout << "fi sum vector1 and vector2: " << v1.sum(v2).fi().getValue() << "\n";

    std::cout << "\n--------------------------\n";

    std::cout << "\nPress Enter to close this window.\n";
    std::cin.get();
}
