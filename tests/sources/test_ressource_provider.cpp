#include "test_ressource_provider.hpp"

#include <memory>
#include <string>

#include <utility/system_io/file.hpp>

using namespace utility;

namespace tests::utility
{
	namespace
	{
		std::shared_ptr<File> shaderFile(const std::string &path)
		{
			return std::make_shared<File>(path, std::string("AAAA"));
		}
	}	 // namespace

	TEST_F(TestRessourceProvider, ExactPathAndShortNameAgree)
	{
		auto shader = _provider.loadShaderFromAssets(shaderFile("text.vs"),
													 shaderFile("text.fs"));
		ASSERT_NE(shader, nullptr);

		const uint32_t byShort = _provider.getShaderID("text");
		const uint32_t byPath  = _provider.getShaderID("text.vs_with_text.fs");

		EXPECT_NE(byShort, 0u);
		EXPECT_EQ(byShort, byPath);
	}

	TEST_F(TestRessourceProvider, UnknownNameReturnsZero)
	{
		_provider.loadShaderFromAssets(shaderFile("text.vs"),
									   shaderFile("text.fs"));
		EXPECT_EQ(_provider.getShaderID("missing"), 0u);
	}

	TEST_F(TestRessourceProvider, AmbiguousPrefixIsDeterministic)
	{
		auto first = _provider.loadShaderFromAssets(shaderFile("alpha.vs"),
													shaderFile("alpha.fs"));
		auto second = _provider.loadShaderFromAssets(shaderFile("alpha.vs"),
													 shaderFile("beta.fs"));
		ASSERT_NE(first, nullptr);
		ASSERT_NE(second, nullptr);

		const uint32_t firstId = _provider.getShaderID("alpha");
		EXPECT_NE(firstId, 0u);
		EXPECT_NE(firstId, _provider.getShaderID("alpha.vs_with_beta.fs"));

		// "alpha.vs_with" matches both shaders; the first registered (lowest
		// id) must win, independently of the container's iteration order.
		for (int i = 0; i < 100; ++i) {
			EXPECT_EQ(_provider.getShaderID("alpha.vs_with"), firstId);
		}
	}

	TEST_F(TestRessourceProvider, NonShaderEntriesAreNotReturned)
	{
		_provider.loadCodePointsFromAsset(
			std::make_shared<File>("text_extra.codepoints", std::string()));
		EXPECT_EQ(_provider.getShaderID("text"), 0u);
	}
}	 // namespace tests::utility
