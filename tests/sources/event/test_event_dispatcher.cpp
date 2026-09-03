#include "event/test_event.hpp"

#include "utility/event/event_dispatcher.hpp"
#include "utility/event/mouse_motion_event.hpp"
#include "utility/event/mouse_button_event.hpp"
#include "utility/math/vector.hpp"

using namespace utility::event;
using namespace utility::math;
using namespace tests::utility::event;

TEST_F(TestEvent, DispatcherInvokesMatchingListener)
{
	EventDispatcher dispatcher;
	MouseMotionEvent event;
	Vector2F pos { 3.0f, 4.0f };
	event.setPosition(pos);

	bool invoked = false;
	Vector2F received { 0, 0 };
	dispatcher.addListener<MouseMotionEvent>([&](const MouseMotionEvent &e) {
		invoked	 = true;
		received = e.getPosition();
	});

	dispatcher.emit(event);
	EXPECT_TRUE(invoked);
	EXPECT_EQ(received, pos);
}

TEST_F(TestEvent, DispatcherIgnoresOtherTypes)
{
	EventDispatcher dispatcher;
	int count = 0;
	dispatcher.addListener<MouseButtonEvent>([&](const MouseButtonEvent &) {
		++count;
	});

	dispatcher.emit(MouseMotionEvent {});
	EXPECT_EQ(count, 0);
}

TEST_F(TestEvent, DispatcherSupportsMultipleListeners)
{
	EventDispatcher dispatcher;
	int count = 0;
	dispatcher.addListener<MouseMotionEvent>([&](const MouseMotionEvent &) {
		++count;
	});
	dispatcher.addListener<MouseMotionEvent>([&](const MouseMotionEvent &) {
		++count;
	});

	dispatcher.emit(MouseMotionEvent {});
	EXPECT_EQ(count, 2);
}

TEST_F(TestEvent, DispatcherClearListeners)
{
	EventDispatcher dispatcher;
	int count = 0;
	dispatcher.addListener<MouseMotionEvent>([&](const MouseMotionEvent &) {
		++count;
	});
	dispatcher.clearListeners<MouseMotionEvent>();
	dispatcher.emit(MouseMotionEvent {});
	EXPECT_EQ(count, 0);
}

TEST_F(TestEvent, DispatcherClearAll)
{
	EventDispatcher dispatcher;
	int count = 0;
	dispatcher.addListener<MouseMotionEvent>([&](const MouseMotionEvent &) {
		++count;
	});
	dispatcher.addListener<MouseButtonEvent>([&](const MouseButtonEvent &) {
		++count;
	});
	dispatcher.clearAll();
	dispatcher.emit(MouseMotionEvent {});
	dispatcher.emit(MouseButtonEvent {});
	EXPECT_EQ(count, 0);
}
