#include "event/test_event.hpp"

#include <sstream>

#include "utility/event/quit_event.hpp"
#include "utility/event/mouse_motion_event.hpp"
#include "utility/event/mouse_button_event.hpp"
#include "utility/event/mouse_wheel_event.hpp"
#include "utility/event/text_input_event.hpp"
#include "utility/math/vector.hpp"

using namespace utility::event;
using namespace utility::math;
using namespace tests::utility::event;

TEST_F(TestEvent, QuitEventFactory)
{
	QuitEvent::Factory factory;
	auto base = factory.create();
	ASSERT_NE(base, nullptr);
	EXPECT_NE(std::dynamic_pointer_cast<QuitEvent>(base), nullptr);

	auto typed = factory.createTyped();
	ASSERT_NE(typed, nullptr);
	EXPECT_NE(std::dynamic_pointer_cast<QuitEvent>(typed), nullptr);
}

TEST_F(TestEvent, MouseMotionDefaults)
{
	MouseMotionEvent event;
	Vector2F zero { 0, 0 };
	EXPECT_EQ(event.getPosition(), zero);
}

TEST_F(TestEvent, MouseMotionSetGetChaining)
{
	MouseMotionEvent event;
	Vector2F pos { 12.5f, 7.0f };
	MouseMotionEvent &ref = event.setPosition(pos);
	EXPECT_EQ(&ref, &event);
	EXPECT_EQ(event.getPosition(), pos);
}

TEST_F(TestEvent, MouseMotionFactory)
{
	MouseMotionEvent::Factory factory;
	auto base = factory.create();
	ASSERT_NE(base, nullptr);
	EXPECT_NE(std::dynamic_pointer_cast<MouseMotionEvent>(base), nullptr);

	auto typed = factory.createTyped();
	ASSERT_NE(typed, nullptr);
	Vector2F zero { 0, 0 };
	EXPECT_EQ(typed->getPosition(), zero);
}

TEST_F(TestEvent, MouseMotionStream)
{
	MouseMotionEvent event;
	Vector2F pos { 2.0f, 3.0f };
	event.setPosition(pos);
	std::ostringstream ss;
	ss << event;
	EXPECT_NE(ss.str().find("MouseMotionEvent"), std::string::npos);
}

TEST_F(TestEvent, MouseButtonDefaults)
{
	MouseButtonEvent event;
	EXPECT_EQ(event.getButton(), MouseButtonEvent::Button::Unknown);
	EXPECT_FALSE(event.isButtonPressed());
	Vector2F zero { 0, 0 };
	EXPECT_EQ(event.getPosition(), zero);
}

TEST_F(TestEvent, MouseButtonSetGetChaining)
{
	MouseButtonEvent event;
	Vector2F pos { 1.0f, 2.0f };
	MouseButtonEvent &ref = event.setButton(MouseButtonEvent::Button::Right)
								.setPressed(true)
								.setPosition(pos);
	EXPECT_EQ(&ref, &event);
	EXPECT_EQ(event.getButton(), MouseButtonEvent::Button::Right);
	EXPECT_TRUE(event.isButtonPressed());
	EXPECT_EQ(event.getPosition(), pos);
}

TEST_F(TestEvent, MouseButtonFactory)
{
	MouseButtonEvent::Factory factory;
	auto typed = factory.createTyped();
	ASSERT_NE(typed, nullptr);
	EXPECT_EQ(typed->getButton(), MouseButtonEvent::Button::Unknown);
}

TEST_F(TestEvent, MouseButtonStream)
{
	MouseButtonEvent event;
	event.setButton(MouseButtonEvent::Button::Left).setPressed(true);
	std::ostringstream ss;
	ss << event;
	EXPECT_NE(ss.str().find("MouseButtonEvent"), std::string::npos);
}

TEST_F(TestEvent, MouseWheelDefaults)
{
	MouseWheelEvent event;
	Vector2F zero { 0, 0 };
	EXPECT_EQ(event.getOffset(), zero);
}

TEST_F(TestEvent, MouseWheelSetGet)
{
	MouseWheelEvent event;
	Vector2F offset { 0.5f, -1.0f };
	event.setOffset(offset);
	EXPECT_EQ(event.getOffset(), offset);
}

TEST_F(TestEvent, MouseWheelFactory)
{
	MouseWheelEvent::Factory factory;
	auto typed = factory.createTyped();
	ASSERT_NE(typed, nullptr);
	Vector2F zero { 0, 0 };
	EXPECT_EQ(typed->getOffset(), zero);
}

TEST_F(TestEvent, TextInputDefaults)
{
	TextInputEvent event;
	EXPECT_TRUE(event.getText().empty());
}

TEST_F(TestEvent, TextInputSetGet)
{
	TextInputEvent event;
	event.setText("hello");
	EXPECT_EQ(event.getText(), "hello");
}

TEST_F(TestEvent, TextInputFactory)
{
	TextInputEvent::Factory factory;
	auto typed = factory.createTyped();
	ASSERT_NE(typed, nullptr);
	EXPECT_TRUE(typed->getText().empty());
}
