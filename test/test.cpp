#include <catch_amalgamated.hpp>
#include <Parser.hpp>


TEST_CASE( "Factorials are computed", "[factorial]" ) {
    Parser parser("test/data/simple.lyx");
    auto res = parser.parse();
    std::stringstream ss;
    res->print_source(ss);

    REQUIRE(ss.str() == "print 5;\n");
}