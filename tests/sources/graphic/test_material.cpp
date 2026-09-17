#include "graphic/test_material.hpp"

#include "utility/graphic/material.hpp"
#include "utility/graphic/text/text_material.hpp"

using namespace tests::utility::graphic;

namespace
{
	/**
	 * @brief A Material that exercises the protected alpha fields the way a
	 * subclass (the intended extension point) would.
	 */
	class ConfigurableMaterial: public ::utility::graphic::Material
	{
		public:
		void configure(::utility::graphic::AlphaMode mode, float cutoff)
		{
			_alphaMode	 = mode;
			_alphaCutoff = cutoff;
		}
	};
}	 // namespace

TEST_F(TestMaterial, DefaultsToOpaqueWithGltfCutoff)
{
	::utility::graphic::Material material;

	EXPECT_EQ(material.getAlphaMode(), ::utility::graphic::AlphaMode::Opaque);
	EXPECT_FLOAT_EQ(material.getAlphaCutoff(), 0.5f);
}

TEST_F(TestMaterial, TextMaterialIsBlend)
{
	::utility::graphic::TextMaterial material;

	EXPECT_EQ(material.getAlphaMode(), ::utility::graphic::AlphaMode::Blend);
	EXPECT_FLOAT_EQ(material.getAlphaCutoff(), 0.5f);
}

TEST_F(TestMaterial, AlphaModeIsSettableBySubclassing)
{
	ConfigurableMaterial material;

	material.configure(::utility::graphic::AlphaMode::Mask, 0.25f);

	EXPECT_EQ(material.getAlphaMode(), ::utility::graphic::AlphaMode::Mask);
	EXPECT_FLOAT_EQ(material.getAlphaCutoff(), 0.25f);
}

TEST_F(TestMaterial, AlphaModeDoesNotBumpVersion)
{
	ConfigurableMaterial material;

	ASSERT_EQ(material.getVersion(), 0u);

	material.configure(::utility::graphic::AlphaMode::Blend, 0.5f);

	EXPECT_EQ(material.getVersion(), 0u)
		<< "_version tracks texture uploads, not alpha classification";
}
