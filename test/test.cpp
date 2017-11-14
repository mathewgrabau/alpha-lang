#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "VariableNode.hpp"

TEST_CASE("Variable nodes have names", "[name]") {
	VariableNode node("name");
	auto name = node.get_name();
	REQUIRE(name == "name");
}

