#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receive.h"




/*Positive test case */
TEST_CASE("Case for Postive test case :- Success of Data ReadFromConsole") {

  REQUIRE(ReadFromConsole(Temperature, Charge_rate) == PASS);
}

/*TEST_CASE("To check if file was successfully opened to read") 
{
  Sender_InType InVal = FileInput ; 
  REQUIRE(InputValue(InVal) == PASS); 
}


TEST_CASE("To check if file was successfully written to console") 
{
  Sender_OutType OutVal = PrintToConsole ;
  REQUIRE(OutputValue(OutVal)== PASS);
  
}*/
