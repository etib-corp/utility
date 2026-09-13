#include "test_ressource_provider.hpp"

#include <map>
#include <memory>
#include <type_traits>

#include "utility/ressource_provider.hpp"
#include "utility/system_io/default_system_io.hpp"

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
