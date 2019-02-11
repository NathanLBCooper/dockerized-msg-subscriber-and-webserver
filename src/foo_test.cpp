#include "../catch/catch.hpp"
#include "consoleLogger.hpp"

using namespace RabbitMqExample;

TEST_CASE( "Exampletest", "[Exampletest]" ) {
    ConsoleLogger logger;
    REQUIRE( 1 == 2 );
}
