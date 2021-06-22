#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receive.h"

TEST_CASE("To check if file was successfully written to console") 
{
  Receiver_OutType OutVal = PrintToConsole ;
  REQUIRE(OutputValue(OutVal)== PASS);
 
}
