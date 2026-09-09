#include <iostream>
#include <string>

#include <utility/cache.hpp>

int main(void)
{
	utility::Cache<std::string, int> scores;

	scores.put("alice", 42);
	scores.emplace("bob", 27);

	if (const auto score = scores.get("alice")) {
		std::cout << "alice: " << *score << "\n";
	}

	std::cout << "contains bob: " << std::boolalpha << scores.contains("bob")
			  << "\n";

	scores.erase("bob");
	std::cout << "contains bob after erase: " << scores.contains("bob") << "\n";

	return 0;
}