#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receive.h"




/*Positive test case */
TEST_CASE("Case for Postive test case :- Success of Data ReadFromConsole") {

  REQUIRE(ReadFromConsole(Temperature, Charge_rate) == PASS);
}

