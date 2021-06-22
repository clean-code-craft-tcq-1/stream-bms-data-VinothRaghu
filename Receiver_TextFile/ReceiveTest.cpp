#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "Receive.h"

TEST_CASE("To check if file was successfully opened to read") 
{
  Receiver_InType InVal = FileInput ; 
  REQUIRE(InputValue(InVal) == PASS); 
}
