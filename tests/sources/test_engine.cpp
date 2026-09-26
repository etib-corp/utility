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

#include "test_engine.hpp"

#include <memory>

#include "utility/engine.hpp"
#include "utility/graphic/scissor.hpp"

namespace tests::utility
{
	namespace
	{
		/**
		 * @brief Minimal concrete engine used to exercise the base class.
		 */
		class StubEngine: public ::utility::Engine
		{
			public:
			void clear(void) override
			{
			}

			void present(void) override
			{
			}

			::utility::graphic::SizeF
				measureText(const ::utility::graphic::Text &) const override
			{
				return { 0.0f, 0.0f };
			}

			size_t createObject(
				std::shared_ptr<::utility::graphic::Renderable>) override
			{
				return 0;
			}

			bool updateObject(std::shared_ptr<::utility::graphic::Renderable>,
							  size_t) override
			{
				return false;
			}

			bool removeObject(std::shared_ptr<::utility::graphic::Renderable>,
							  size_t) override
			{
				return false;
			}

			::utility::graphic::ViewF getView(void) const override
			{
				return ::utility::graphic::ViewF();
			}

			void pollEvents(void) override
			{
			}

			void update(void) override
			{
			}
		};
	}	 // namespace

	TEST_F(TestEngine, DefaultDeltaTimeIsZero)
	{
		StubEngine engine;

		EXPECT_FLOAT_EQ(engine.getDeltaTime(), 0.0f);
	}

	TEST_F(TestEngine, ScissorDefaultsToNullopt)
	{
		StubEngine engine;

		EXPECT_FALSE(engine.getScissor().has_value());
	}

	TEST_F(TestEngine, SetScissorStoresRectangle)
	{
		StubEngine engine;

		const ::utility::graphic::ScissorRect rect { 1.0f, 2.0f, 30.0f, 40.0f };
		engine.setScissor(rect);

		ASSERT_TRUE(engine.getScissor().has_value());
		EXPECT_EQ(engine.getScissor().value(), rect);
	}

	TEST_F(TestEngine, ClearScissorRemovesRectangle)
	{
		StubEngine engine;

		engine.setScissor(
			::utility::graphic::ScissorRect { 1.0f, 2.0f, 3.0f, 4.0f });
		engine.clearScissor();

		EXPECT_FALSE(engine.getScissor().has_value());
	}

	TEST_F(TestEngine, ScissorRectEquality)
	{
		const ::utility::graphic::ScissorRect first { 1.0f, 2.0f, 3.0f, 4.0f };
		const ::utility::graphic::ScissorRect same { 1.0f, 2.0f, 3.0f, 4.0f };
		const ::utility::graphic::ScissorRect other { 1.0f, 2.0f, 3.0f, 5.0f };

		EXPECT_EQ(first, same);
		EXPECT_NE(first, other);
	}

}	 // namespace tests::utility
