#include "event/test_event.hpp"

#include "utility/event/mouse_motion_event.hpp"
#include "utility/event/mouse_button_event.hpp"
#include "utility/event/quit_event.hpp"
#include "utility/math/vector.hpp"

using namespace utility::event;
using namespace utility::math;
using namespace tests::utility::event;

TEST_F(TestEvent, MouseMotionDefaults)
{
	MouseMotionEvent event;
	Vector2F expected{ 0, 0 };
	EXPECT_EQ(event.getPosition(), expected);
}

TEST_F(TestEvent, MouseMotionSetAndGet)
{
	MouseMotionEvent event;
	Vector2F pos{ 12.5f, 7.0f };
	event.setPosition(pos);
	EXPECT_EQ(event.getPosition(), pos);
}

TEST_F(TestEvent, MouseMotionFactoryCreatesTypedEvent)
{
	MouseMotionEvent::Factory factory;
	auto event = factory.createTyped();
	Vector2F zero{ 0, 0 };
	ASSERT_NE(event, nullptr);
	EXPECT_EQ(event->getPosition(), zero);
}

TEST_F(TestEvent, MouseMotionFactoryCreatesBaseEvent)
{
	MouseMotionEvent::Factory factory;
	auto event = factory.create();
	ASSERT_NE(event, nullptr);
	EXPECT_NE(std::dynamic_pointer_cast<MouseMotionEvent>(event), nullptr);
}

TEST_F(TestEvent, MouseButtonDefaults)
{
	MouseButtonEvent event;
	EXPECT_EQ(event.getButton(), MouseButtonEvent::Button::Unknown);
	EXPECT_FALSE(event.isButtonPressed());
}

TEST_F(TestEvent, MouseButtonSetters)
{
	MouseButtonEvent event;
	Vector2F pos{ 1.0f, 2.0f };
	event.setButton(MouseButtonEvent::Button::Right)
		.setPressed(true)
		.setPosition(pos);
	EXPECT_EQ(event.getButton(), MouseButtonEvent::Button::Right);
	EXPECT_TRUE(event.isButtonPressed());
	EXPECT_EQ(event.getPosition(), pos);
}

TEST_F(TestEvent, MouseButtonFactoryCreatesTypedEvent)
{
	MouseButtonEvent::Factory factory;
	auto event = factory.createTyped();
	ASSERT_NE(event, nullptr);
	EXPECT_EQ(event->getButton(), MouseButtonEvent::Button::Unknown);
}

TEST_F(TestEvent, QuitEventFactoryCreatesBaseEvent)
{
	QuitEvent::Factory factory;
	auto event = factory.create();
	ASSERT_NE(event, nullptr);
	EXPECT_NE(std::dynamic_pointer_cast<QuitEvent>(event), nullptr);
}
