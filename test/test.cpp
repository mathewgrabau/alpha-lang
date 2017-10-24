#define CATCH_CONFIG_MAIN	// This tells Catch to provide a main() - only do this in one cpp file.
#include "catch.hpp"

#include "VariableNode.hpp"

TEST_CASE("Variable nodes have names", "[name]") {
	REQUIRE(VariableNode("Dummy").get_name() == "Dummy");
}

