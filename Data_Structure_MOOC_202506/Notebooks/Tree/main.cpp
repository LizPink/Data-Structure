/* Tree Main */
#include <iostream>
#include "Tree01.hpp"
#include "Tree02.hpp"

int main()
{
    BinNode<int> node1;

    int b  = 100;
    const int a = b;
    int const c = b;
    int const& d = b;
    std::cout << a << c << d << std::endl;

    return 0;
}