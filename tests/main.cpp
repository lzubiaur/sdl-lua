// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

  int rc = Catch::Session().run(argc, argv);

  return rc;
}
