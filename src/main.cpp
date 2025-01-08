#include "Parser.hpp"

#include <iostream>

int main()
{
    {
        Parser parser("test.lyx");
        auto res = parser.parse();
        std::cout << "Tree:\n";
        res->print_tree(std::cout);
        std::cout << "\nReconstructed Source:\n";
        res->print_source(std::cout);
        std::cout << "\n";
        std::cout << res.get()->get_sector() << std::endl;
        std::cout << res.get() << std::endl;
    }

    return 0;
}