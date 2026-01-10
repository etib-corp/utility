/*
 Copyright (c) 2026 ETIB Corporation

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "test_rectangle.hpp"
#include "rectangle.hpp"
#include "vector.hpp"
#include <gtest/gtest.h>
#include <sstream>

namespace utility {

// Test default constructor
TEST_F(TestRectangle, DefaultConstructor) {
  Rectangle<int> rect;
  EXPECT_EQ(rect.x(), 0);
  EXPECT_EQ(rect.y(), 0);
  EXPECT_EQ(rect.width(), 0);
  EXPECT_EQ(rect.height(), 0);
}

// Test parameterized constructor
TEST_F(TestRectangle, ParameterizedConstructor) {
  Rectangle<int> rect(10, 20, 30, 40);
  EXPECT_EQ(rect.x(), 10);
  EXPECT_EQ(rect.y(), 20);
  EXPECT_EQ(rect.width(), 30);
  EXPECT_EQ(rect.height(), 40);
}

// Test negative dimensions throw exception
TEST_F(TestRectangle, NegativeDimensionsThrow) {
  EXPECT_THROW(Rectangle<int>(0, 0, -10, 20), std::invalid_argument);
  EXPECT_THROW(Rectangle<int>(0, 0, 10, -20), std::invalid_argument);
}

// Test copy constructor
TEST_F(TestRectangle, CopyConstructor) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2(rect1);
  EXPECT_EQ(rect2.x(), 10);
  EXPECT_EQ(rect2.y(), 20);
  EXPECT_EQ(rect2.width(), 30);
  EXPECT_EQ(rect2.height(), 40);
}

// Test move constructor
TEST_F(TestRectangle, MoveConstructor) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2(std::move(rect1));
  EXPECT_EQ(rect2.x(), 10);
  EXPECT_EQ(rect2.y(), 20);
  EXPECT_EQ(rect2.width(), 30);
  EXPECT_EQ(rect2.height(), 40);
}

// Test copy assignment
TEST_F(TestRectangle, CopyAssignment) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2;
  rect2 = rect1;
  EXPECT_EQ(rect2.x(), 10);
  EXPECT_EQ(rect2.y(), 20);
  EXPECT_EQ(rect2.width(), 30);
  EXPECT_EQ(rect2.height(), 40);
}

// Test move assignment
TEST_F(TestRectangle, MoveAssignment) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2;
  rect2 = std::move(rect1);
  EXPECT_EQ(rect2.x(), 10);
  EXPECT_EQ(rect2.y(), 20);
  EXPECT_EQ(rect2.width(), 30);
  EXPECT_EQ(rect2.height(), 40);
}

// Test setters
TEST_F(TestRectangle, Setters) {
  Rectangle<int> rect;
  rect.setX(5);
  rect.setY(10);
  rect.setWidth(15);
  rect.setHeight(20);
  EXPECT_EQ(rect.x(), 5);
  EXPECT_EQ(rect.y(), 10);
  EXPECT_EQ(rect.width(), 15);
  EXPECT_EQ(rect.height(), 20);
}

// Test setters throw on negative dimensions
TEST_F(TestRectangle, SettersThrowOnNegative) {
  Rectangle<int> rect(0, 0, 10, 10);
  EXPECT_THROW(rect.setWidth(-5), std::invalid_argument);
  EXPECT_THROW(rect.setHeight(-5), std::invalid_argument);
}

// Test edge and center methods
TEST_F(TestRectangle, EdgesAndCenter) {
  Rectangle<int> rect(10, 20, 30, 40);
  EXPECT_EQ(rect.right(), 40);
  EXPECT_EQ(rect.bottom(), 60);
  EXPECT_EQ(rect.centerX(), 25);
  EXPECT_EQ(rect.centerY(), 40);
}

// Test area calculation
TEST_F(TestRectangle, Area) {
  Rectangle<int> rect(0, 0, 10, 20);
  EXPECT_EQ(rect.area(), 200);
}

// Test perimeter calculation
TEST_F(TestRectangle, Perimeter) {
  Rectangle<int> rect(0, 0, 10, 20);
  EXPECT_EQ(rect.perimeter(), 60);
}

// Test contains point
TEST_F(TestRectangle, ContainsPoint) {
  Rectangle<int> rect(0, 0, 10, 10);
  EXPECT_TRUE(rect.contains(Vector<int, 2>{5, 5}));
  EXPECT_TRUE(rect.contains(Vector<int, 2>{0, 0}));
  EXPECT_TRUE(rect.contains(Vector<int, 2>{10, 10}));
  EXPECT_FALSE(rect.contains(Vector<int, 2>{-1, 5}));
  EXPECT_FALSE(rect.contains(Vector<int, 2>{5, 11}));
}

// Test intersects
TEST_F(TestRectangle, Intersects) {
  Rectangle<int> rect1(0, 0, 10, 10);
  Rectangle<int> rect2(5, 5, 10, 10);
  Rectangle<int> rect3(20, 20, 10, 10);
  EXPECT_TRUE(rect1.intersects(rect2));
  EXPECT_TRUE(rect2.intersects(rect1));
  EXPECT_FALSE(rect1.intersects(rect3));
  EXPECT_FALSE(rect3.intersects(rect1));
}

// Test containsRectangle
TEST_F(TestRectangle, ContainsRectangle) {
  Rectangle<int> rect1(0, 0, 20, 20);
  Rectangle<int> rect2(5, 5, 5, 5);
  Rectangle<int> rect3(15, 15, 10, 10);
  EXPECT_TRUE(rect1.containsRectangle(rect2));
  EXPECT_FALSE(rect2.containsRectangle(rect1));
  EXPECT_FALSE(rect1.containsRectangle(rect3));
}

// Test equality operators
TEST_F(TestRectangle, EqualityOperators) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2(10, 20, 30, 40);
  Rectangle<int> rect3(10, 20, 30, 41);
  EXPECT_TRUE(rect1 == rect2);
  EXPECT_FALSE(rect1 == rect3);
  EXPECT_FALSE(rect1 != rect2);
  EXPECT_TRUE(rect1 != rect3);
}

// Test translate
TEST_F(TestRectangle, Translate) {
  Rectangle<int> rect(10, 20, 30, 40);
  rect.translate(5, -10);
  EXPECT_EQ(rect.x(), 15);
  EXPECT_EQ(rect.y(), 10);
  EXPECT_EQ(rect.width(), 30);
  EXPECT_EQ(rect.height(), 40);
}

// Test translated
TEST_F(TestRectangle, Translated) {
  Rectangle<int> rect1(10, 20, 30, 40);
  Rectangle<int> rect2 = rect1.translated(Vector<int, 2>{5, -10});
  EXPECT_EQ(rect1.x(), 10);
  EXPECT_EQ(rect1.y(), 20);
  EXPECT_EQ(rect2.x(), 15);
  EXPECT_EQ(rect2.y(), 10);
}

// Test scale
TEST_F(TestRectangle, Scale) {
  Rectangle<double> rect(10.0, 10.0, 20.0, 20.0);
  rect.scale(2.0);
  EXPECT_DOUBLE_EQ(rect.width(), 40.0);
  EXPECT_DOUBLE_EQ(rect.height(), 40.0);
  EXPECT_DOUBLE_EQ(rect.centerX(), 20.0);
  EXPECT_DOUBLE_EQ(rect.centerY(), 20.0);
}

// Test scale throws on negative factor
TEST_F(TestRectangle, ScaleThrowsOnNegative) {
  Rectangle<double> rect(0.0, 0.0, 10.0, 10.0);
  EXPECT_THROW(rect.scale(-1.0), std::invalid_argument);
}

// Test scaled
TEST_F(TestRectangle, Scaled) {
  Rectangle<double> rect1(10.0, 10.0, 20.0, 20.0);
  Rectangle<double> rect2 = rect1.scaled(2.0);
  EXPECT_DOUBLE_EQ(rect1.width(), 20.0);
  EXPECT_DOUBLE_EQ(rect2.width(), 40.0);
  EXPECT_DOUBLE_EQ(rect2.centerX(), 20.0);
  EXPECT_DOUBLE_EQ(rect2.centerY(), 20.0);
}

// Test stream output
TEST_F(TestRectangle, StreamOutput) {
  Rectangle<int> rect(10, 20, 30, 40);
  std::ostringstream oss;
  oss << rect;
  EXPECT_EQ(oss.str(), "Rectangle(10, 20, 30, 40)");
}

// Test with floating point
TEST_F(TestRectangle, FloatingPoint) {
  Rectangle<double> rect(1.5, 2.5, 3.5, 4.5);
  EXPECT_DOUBLE_EQ(rect.x(), 1.5);
  EXPECT_DOUBLE_EQ(rect.y(), 2.5);
  EXPECT_DOUBLE_EQ(rect.width(), 3.5);
  EXPECT_DOUBLE_EQ(rect.height(), 4.5);
  EXPECT_DOUBLE_EQ(rect.area(), 15.75);
}

// Test position and size vectors
TEST_F(TestRectangle, PositionAndSizeVectors) {
  Vector<int, 2> pos{10, 20};
  Vector<int, 2> size{30, 40};
  Rectangle<int> rect(pos, size);
  EXPECT_EQ(rect.x(), 10);
  EXPECT_EQ(rect.y(), 20);
  EXPECT_EQ(rect.width(), 30);
  EXPECT_EQ(rect.height(), 40);
  EXPECT_EQ(rect.getPosition(), pos);
  EXPECT_EQ(rect.getSize(), size);
}

// Test Vector-based equality
TEST_F(TestRectangle, VectorBasedEquality) {
  Vector<int, 2> pos{5, 10};
  Vector<int, 2> size{20, 25};
  Rectangle<int> rect1(pos, size);
  Rectangle<int> rect2(pos, size);
  Vector<int, 2> size3{20, 26};
  Rectangle<int> rect3(pos, size3);
  // Vectors should compare equal when positions and sizes match
  EXPECT_TRUE(rect1 == rect2);
  EXPECT_FALSE(rect1 == rect3);
}

// Test that coordinate changes properly update position vector
TEST_F(TestRectangle, PositionVectorUpdates) {
  Vector<int, 2> pos{0, 0};
  Vector<int, 2> size{10, 10};
  Rectangle<int> rect(pos, size);
  rect.setX(15);
  EXPECT_EQ(rect.x(), 15);
  rect.setY(25);
  EXPECT_EQ(rect.y(), 25);
  // Other coordinates should remain unchanged
  EXPECT_EQ(rect.width(), 10);
  EXPECT_EQ(rect.height(), 10);
}

// Test that size changes properly update size vector
TEST_F(TestRectangle, SizeVectorUpdates) {
  Vector<int, 2> pos{5, 10};
  Vector<int, 2> size{20, 30};
  Rectangle<int> rect(pos, size);
  rect.setWidth(50);
  EXPECT_EQ(rect.width(), 50);
  rect.setHeight(60);
  EXPECT_EQ(rect.height(), 60);
  // Other coordinates should remain unchanged
  EXPECT_EQ(rect.x(), 5);
  EXPECT_EQ(rect.y(), 10);
}

} // namespace utility
