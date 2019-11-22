#include "catch.hpp"
#include "enemy.h"

// ofxUnitTests IS AN OPTION

//TEST_CASE("test") { REQUIRE(true); }

//TEST_CASE("path plotter returns a randomized vector of std::pairs") { 
//  Enemy enemy;
//  std::vector<std::pair<int, int>> compare = enemy.path_plotter();
//  int expected_size = 100;
//  REQUIRE(compare.size() == expected_size); 
//
//  for (size_t i = 1; i < compare.size(); i++) {
//      REQUIRE(compare[i].first == compare[i - 1].first);
//  }
//}