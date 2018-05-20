#include <cstring>

#include "catch.hpp"
#include "list.h"

TEST_CASE("Creating Links", "[Link]") {
  Link link = Link{"link", nullptr, nullptr};
  REQUIRE(strcmp(link.value, "link") == 0);
}


