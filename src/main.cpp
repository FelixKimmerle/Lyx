#include "Parser.hpp"

#include <iostream>

int main()
{
    {
        Parser parser("test.lyx");
        auto res = parser.parse();
        std::cout << res.get()->get_sector() << std::endl;
        std::cout << res.get() << std::endl;
    }

    return 0;
}