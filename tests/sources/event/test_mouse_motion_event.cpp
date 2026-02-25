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

#include "event/test_mouse_motion_event.hpp"

TEST_F(TestMouseMotionEvent, DefaultPositionIsOrigin) {
	utility::event::MouseMotionEvent event;
	const auto position = event.getPosition();

	EXPECT_FLOAT_EQ(position[0], 0.0F);
	EXPECT_FLOAT_EQ(position[1], 0.0F);
}

TEST_F(TestMouseMotionEvent, PositionCanBeUpdated) {
	utility::event::MouseMotionEvent event;

	event.setPosition({12.5F, -7.25F});

	const auto position = event.getPosition();
	EXPECT_FLOAT_EQ(position[0], 12.5F);
	EXPECT_FLOAT_EQ(position[1], -7.25F);
}
