#include "test_ressource_provider.hpp"

#include <memory>
#include <string>
#include <map>
#include <type_traits>

#include "utility/ressource_provider.hpp"
#include "utility/system_io/default_system_io.hpp"

#include <utility/system_io/file.hpp>

using namespace utility;

// The accessors must hand out a reference to the provider's own container,
// never a by-value copy (see docs/PERFORMANCE_AUDIT_UTILITY.md, Finding 2).
static_assert(
	std::is_same_v<
		decltype(std::declval<const RessourceProvider &>().getMaterials()),
		const std::map<uint32_t, std::shared_ptr<graphic::Material>> &>,
	"getMaterials() must return a const reference");
static_assert(
	std::is_same_v<
		decltype(std::declval<const RessourceProvider &>().getTextures()),
		const std::map<uint32_t, std::shared_ptr<graphic::Texture>> &>,
	"getTextures() must return a const reference");
static_assert(
	std::is_same_v<
		decltype(std::declval<const RessourceProvider &>().getModels()),
		const std::map<uint32_t, std::shared_ptr<graphic::Model>> &>,
	"getModels() must return a const reference");
static_assert(
	std::is_same_v<
		decltype(std::declval<const RessourceProvider &>().getShaders()),
		const std::map<uint32_t, std::shared_ptr<graphic::Shader>> &>,
	"getShaders() must return a const reference");
static_assert(
	std::is_same_v<
		decltype(std::declval<const RessourceProvider &>().getCodePoints()),
		const std::map<uint32_t, std::shared_ptr<graphic::CodePoints>> &>,
	"getCodePoints() must return a const reference");


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

	TEST_F(TestRessourceProvider, AccessorsReturnReferenceToInternalMap)
	{
		DefaultSystemIO systemIO;
		RessourceProvider provider(systemIO);

		// Two calls on a by-value accessor would return distinct addresses;
		// identical addresses prove the internal container is returned.
		EXPECT_EQ(&provider.getMaterials(), &provider.getMaterials());
		EXPECT_EQ(&provider.getTextures(), &provider.getTextures());
		EXPECT_EQ(&provider.getModels(), &provider.getModels());
		EXPECT_EQ(&provider.getShaders(), &provider.getShaders());
		EXPECT_EQ(&provider.getCodePoints(), &provider.getCodePoints());
	}

	TEST_F(TestRessourceProvider, AccessorsAreUsableOnConstInstance)
	{
		DefaultSystemIO systemIO;
		const RessourceProvider provider(systemIO);

		EXPECT_TRUE(provider.getMaterials().empty());
		EXPECT_TRUE(provider.getTextures().empty());
		EXPECT_TRUE(provider.getModels().empty());
		EXPECT_TRUE(provider.getShaders().empty());
		EXPECT_TRUE(provider.getCodePoints().empty());
	}
}	 // namespace tests::utility
