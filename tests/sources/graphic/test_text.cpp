#include "graphic/test_text.hpp"

#include "utility/graphic/text.hpp"

using namespace utility::graphic;
using namespace tests::utility::graphic;

TEST_F(TestText, DefaultConstructor) {
  Text text;
  EXPECT_EQ(text.getContent(), "");
  EXPECT_EQ(text.getFontPath(), "");
  EXPECT_FLOAT_EQ(text.getFontSize(), 12.0f);
  EXPECT_EQ(text.getColor().getAlpha(), 255);
}

TEST_F(TestText, SettersAndGetters) {
  Text text;
  PoseF pose;
  Color32Bit color(255, 0, 0, 128);

  text.setContent("Hello")
      .setFontPath("/tmp/font.ttf")
      .setFontSize(24.0f)
      .setColor(color);

  EXPECT_EQ(text.getContent(), "Hello");
  EXPECT_EQ(text.getFontPath(), "/tmp/font.ttf");
  EXPECT_FLOAT_EQ(text.getFontSize(), 24.0f);
  EXPECT_EQ(text.getColor(), color);
}

TEST_F(TestText, ConvenienceAndComparisonHelpers) {
  Text a;
  Text b;

  EXPECT_TRUE(a.empty());
  EXPECT_FALSE(a.hasFontPath());
  EXPECT_TRUE(a == b);

  a.setContent("abc").setFontPath("/tmp/font.ttf");
  EXPECT_FALSE(a.empty());
  EXPECT_TRUE(a.hasFontPath());
  EXPECT_TRUE(a != b);

  a.clearContent();
  EXPECT_TRUE(a.empty());
}
