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

#include "event/test_controller_event.hpp"

TEST_F(TestControllerEvent, ControllerButtonEventStoresHandButtonAndStates) {
  utility::event::ControllerButtonEvent event;

  event.setControllerType(utility::event::ControllerEvent::ControllerType::Right);
  event.setButton(utility::event::ControllerButtonEvent::Button::Menu)
      .setTouched(true)
      .setClicked(true);

  EXPECT_EQ(event.getControllerType(),
            utility::event::ControllerEvent::ControllerType::Right);
  EXPECT_EQ(event.getButton(),
            utility::event::ControllerButtonEvent::Button::Menu);
  EXPECT_TRUE(event.isTouched());
  EXPECT_TRUE(event.isClicked());
}

TEST_F(TestControllerEvent, ControllerMotionEventStoresAimAndGripPoses) {
  utility::event::ControllerMotionEvent event;

  const utility::event::Pose aim{{1.0F, 2.0F, 3.0F}, {4.0F, 5.0F, 6.0F}};
  const utility::event::Pose grip{{-1.0F, -2.0F, -3.0F}, {-4.0F, -5.0F, -6.0F}};

  event.setControllerType(utility::event::ControllerEvent::ControllerType::Left);
  event.setAim(aim).setGrip(grip);

  EXPECT_EQ(event.getControllerType(),
            utility::event::ControllerEvent::ControllerType::Left);

  const auto storedAim = event.getAim();
  EXPECT_FLOAT_EQ(storedAim.position[0], 1.0F);
  EXPECT_FLOAT_EQ(storedAim.position[1], 2.0F);
  EXPECT_FLOAT_EQ(storedAim.position[2], 3.0F);
  EXPECT_FLOAT_EQ(storedAim.orientation[0], 4.0F);
  EXPECT_FLOAT_EQ(storedAim.orientation[1], 5.0F);
  EXPECT_FLOAT_EQ(storedAim.orientation[2], 6.0F);

  const auto storedGrip = event.getGrip();
  EXPECT_FLOAT_EQ(storedGrip.position[0], -1.0F);
  EXPECT_FLOAT_EQ(storedGrip.position[1], -2.0F);
  EXPECT_FLOAT_EQ(storedGrip.position[2], -3.0F);
  EXPECT_FLOAT_EQ(storedGrip.orientation[0], -4.0F);
  EXPECT_FLOAT_EQ(storedGrip.orientation[1], -5.0F);
  EXPECT_FLOAT_EQ(storedGrip.orientation[2], -6.0F);
}

TEST_F(TestControllerEvent, ThumbStickAxisIsClampedToMinusOneOne) {
  utility::event::ControllerThumbStickEvent event;

  event.setAxis(2.0F, -4.0F);

  EXPECT_FLOAT_EQ(event.getX(), 1.0F);
  EXPECT_FLOAT_EQ(event.getY(), -1.0F);
}

TEST_F(TestControllerEvent, TriggerValueIsClampedToZeroOne) {
  utility::event::ControllerTriggerEvent event;

  event.setValue(-0.25F);
  EXPECT_FLOAT_EQ(event.getValue(), 0.0F);

  event.setValue(1.75F);
  EXPECT_FLOAT_EQ(event.getValue(), 1.0F);
}

TEST_F(TestControllerEvent, ThumbRestStoresTouchAndProximityStates) {
  utility::event::ControllerThumbRestEvent event;

  event.setControllerType(utility::event::ControllerEvent::ControllerType::Right);
  event.setTouched(true).setProximity(true);

  EXPECT_EQ(event.getControllerType(),
            utility::event::ControllerEvent::ControllerType::Right);
  EXPECT_TRUE(event.isTouched());
  EXPECT_TRUE(event.isProximity());
}

TEST_F(TestControllerEvent, HandEventsStoreExpectedData) {
  utility::event::HandPinchEvent pinch;
  utility::event::HandPokeEvent poke;
  utility::event::PalmEvent palm;

  // HandPinchEvent and HandPokeEvent currently act as marker events.
  EXPECT_NO_THROW((void)pinch);
  EXPECT_NO_THROW((void)poke);

  palm.setPosition({7.0F, 8.0F, 9.0F}).setOrientation({10.0F, 11.0F, 12.0F});

  const auto palmPosition = palm.getPosition();
  const auto palmOrientation = palm.getOrientation();
  EXPECT_FLOAT_EQ(palmPosition[0], 7.0F);
  EXPECT_FLOAT_EQ(palmPosition[1], 8.0F);
  EXPECT_FLOAT_EQ(palmPosition[2], 9.0F);
  EXPECT_FLOAT_EQ(palmOrientation[0], 10.0F);
  EXPECT_FLOAT_EQ(palmOrientation[1], 11.0F);
  EXPECT_FLOAT_EQ(palmOrientation[2], 12.0F);
}

TEST_F(TestControllerEvent, FactoriesCreateExpectedConcreteTypes) {
  utility::event::ControllerButtonEvent::Factory buttonFactory;
  utility::event::ControllerMotionEvent::Factory motionFactory;
  utility::event::ControllerThumbStickEvent::Factory thumbStickFactory;
  utility::event::ControllerTriggerEvent::Factory triggerFactory;
  utility::event::ControllerThumbRestEvent::Factory thumbRestFactory;
  utility::event::HandPinchEvent::Factory pinchFactory;
  utility::event::HandPokeEvent::Factory pokeFactory;
  utility::event::PalmEvent::Factory palmFactory;

  const auto buttonEvent = buttonFactory.create();
  EXPECT_NE(
      dynamic_cast<utility::event::ControllerButtonEvent *>(buttonEvent.get()),
      nullptr);

  const auto motionEvent = motionFactory.create();
  EXPECT_NE(
      dynamic_cast<utility::event::ControllerMotionEvent *>(motionEvent.get()),
      nullptr);

  const auto thumbStickEvent = thumbStickFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::ControllerThumbStickEvent *>(
                thumbStickEvent.get()),
            nullptr);

  const auto triggerEvent = triggerFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::ControllerTriggerEvent *>(
                triggerEvent.get()),
            nullptr);

  const auto thumbRestEvent = thumbRestFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::ControllerThumbRestEvent *>(
                thumbRestEvent.get()),
            nullptr);

  const auto pinchEvent = pinchFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::HandPinchEvent *>(pinchEvent.get()),
            nullptr);

  const auto pokeEvent = pokeFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::HandPokeEvent *>(pokeEvent.get()),
            nullptr);

  const auto palmEvent = palmFactory.create();
  EXPECT_NE(dynamic_cast<utility::event::PalmEvent *>(palmEvent.get()),
            nullptr);
}
