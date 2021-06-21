#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receive.h"




/*Positive test case */
TEST_CASE("Case for Postive test case :- Success of Data ReadFromConsole") {

  REQUIRE(ReadFromConsole(Temperature, Charge_rate) == PASS);
}

TEST_CASE("Case for Postive test case :- Temp Minvalue") {

  REQUIRE(Calc_MinValue(Temperature == PASS);
}

TEST_CASE("Case for Postive test case :- Temp Maxvalue") {

  REQUIRE(Calc_MaxValue(Temperature == PASS);
}

TEST_CASE("Case for Postive test case :- Charge_rate MaxValue") {

  REQUIRE(Calc_MaxValue(Charge_rate == PASS);
}
    
 TEST_CASE("Case for Postive test case :- Charge_rate Min VAlue") {

  REQUIRE(Calc_MinValue(Charge_rate == PASS);
}
