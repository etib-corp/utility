/*
 Copyright (c) 2025 ETIB Corporation

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

#pragma once

#include <chrono>
#include <cstdint>
#include <ostream>

#include "Vector.hpp"

namespace utility {

/**
 * @brief Enumeration of event types for desktop, AR, and VR environments
 */
enum class EventType : uint8_t {
  // Input Events
  KeyPress,
  KeyRelease,
  MouseMove,
  MouseButtonPress,
  MouseButtonRelease,
  MouseScroll,

  // Touch Events
  TouchBegin,
  TouchMove,
  TouchEnd,
  TouchCancel,

  // Controller/Hand Tracking Events (VR/AR)
  ControllerButtonPress,
  ControllerButtonRelease,
  ControllerAxisMotion,
  ControllerTrigger,
  ControllerGrip,
  HandTrackingUpdate,
  GestureSwipe,
  GesturePinch,
  GestureRotate,

  // Head Tracking Events (VR/AR)
  HeadPoseUpdate,
  EyeGazeUpdate,

  // System Events
  WindowClose,
  WindowResize,
  WindowFocus,
  WindowBlur,
  ApplicationPause,
  ApplicationResume,

  // Spatial Events (AR/VR)
  PlaneDetected,
  PlaneUpdated,
  ImageTracked,
  FaceDetected,
  ObjectDetected,

  // Custom Event
  Custom
};

/**
 * @brief Enumeration for mouse button types
 */
enum class MouseButton : uint8_t {
  Left = 0,
  Middle = 1,
  Right = 2,
  Button4 = 3,
  Button5 = 4
};

/**
 * @brief Enumeration for keyboard modifiers
 */
enum class KeyModifier : uint8_t {
  None = 0x00,
  Shift = 0x01,
  Ctrl = 0x02,
  Alt = 0x04,
  Super = 0x08
};

/**
 * @brief Base Event class for managing events in AR/VR and desktop environments
 */
class Event {
protected:
  EventType _type;
  uint64_t _timestamp;

public:
  /**
   * @brief Construct an event with a specific type
   *
   * @param type The type of event
   */
  explicit Event(EventType type);

  /**
   * @brief Virtual destructor
   */
  virtual ~Event(void) = default;

  /**
   * @brief Get the event type
   *
   * @return EventType The type of this event
   */
  EventType getType(void) const;

  /**
   * @brief Get the event timestamp (milliseconds since epoch)
   *
   * @return uint64_t The timestamp
   */
  uint64_t getTimestamp(void) const;

  /**
   * @brief Check if this event is of a specific type
   *
   * @param type The type to check
   * @return bool True if this event is of the specified type
   */
  bool isType(EventType type) const;
};

/**
 * @brief Keyboard event class
 */
class KeyboardEvent : public Event {
private:
  int _keyCode;
  KeyModifier _modifiers;

public:
  /**
   * @brief Construct a keyboard event
   *
   * @param type Either KeyPress or KeyRelease
   * @param keyCode The key code
   * @param modifiers Keyboard modifiers (shift, ctrl, alt, etc.)
   */
  KeyboardEvent(EventType type, int keyCode,
                KeyModifier modifiers = KeyModifier::None);

  int getKeyCode(void) const;
  KeyModifier getModifiers(void) const;
};

/**
 * @brief Mouse event class
 */
class MouseEvent : public Event {
private:
  Vector<float, 2> _position;
  Vector<float, 2> _delta;
  MouseButton _button;
  KeyModifier _modifiers;

public:
  /**
   * @brief Construct a mouse event
   *
   * @param type The type of mouse event
   * @param position The mouse position in screen coordinates
   * @param delta The mouse movement delta
   * @param button The mouse button (for button events)
   * @param modifiers Keyboard modifiers
   */
  MouseEvent(EventType type, const Vector<float, 2> &position,
             const Vector<float, 2> &delta = Vector<float, 2>(0.0f, 0.0f),
             MouseButton button = MouseButton::Left,
             KeyModifier modifiers = KeyModifier::None);

  const Vector<float, 2> &getPosition(void) const;
  const Vector<float, 2> &getDelta(void) const;
  MouseButton getButton(void) const;
  KeyModifier getModifiers(void) const;
};

/**
 * @brief Touch event class for multi-touch input
 */
class TouchEvent : public Event {
private:
  Vector<float, 2> _position;
  float _pressure;
  uint32_t _touchId;
  int _touchCount;

public:
  /**
   * @brief Construct a touch event
   *
   * @param type The type of touch event
   * @param position The touch position
   * @param pressure The touch pressure (0.0 to 1.0)
   * @param touchId Unique identifier for this touch
   * @param touchCount Total number of active touches
   */
  TouchEvent(EventType type, const Vector<float, 2> &position,
             float pressure = 1.0f, uint32_t touchId = 0, int touchCount = 1);

  const Vector<float, 2> &getPosition(void) const;
  float getPressure(void) const;
  uint32_t getTouchId(void) const;
  int getTouchCount(void) const;
};

/**
 * @brief Controller event class for VR/AR controller input
 */
class ControllerEvent : public Event {
private:
  int _controllerIndex;
  float _axisValue;
  Vector<float, 3> _position;
  Vector<float, 3> _rotation;

public:
  /**
   * @brief Construct a controller event
   *
   * @param type The type of controller event
   * @param controllerIndex Which controller (0 = left, 1 = right)
   * @param axisValue The axis value for analog inputs
   * @param position The 3D position of the controller
   * @param rotation The 3D rotation of the controller
   */
  ControllerEvent(
      EventType type, int controllerIndex, float axisValue = 0.0f,
      const Vector<float, 3> &position = Vector<float, 3>(0.0f, 0.0f, 0.0f),
      const Vector<float, 3> &rotation = Vector<float, 3>(0.0f, 0.0f, 0.0f));

  int getControllerIndex(void) const;
  float getAxisValue(void) const;
  const Vector<float, 3> &getPosition(void) const;
  const Vector<float, 3> &getRotation(void) const;
};

/**
 * @brief Hand tracking event class for VR/AR hand gestures
 */
class HandTrackingEvent : public Event {
private:
  int _handIndex;
  Vector<float, 3> _palmPosition;
  Vector<float, 3> _palmRotation;
  float _confidence;

public:
  /**
   * @brief Construct a hand tracking event
   *
   * @param type The type of hand tracking event
   * @param handIndex Which hand (0 = left, 1 = right)
   * @param palmPosition The 3D position of the palm
   * @param palmRotation The 3D rotation of the palm
   * @param confidence Tracking confidence (0.0 to 1.0)
   */
  HandTrackingEvent(
      EventType type, int handIndex,
      const Vector<float, 3> &palmPosition = Vector<float, 3>(0.0f, 0.0f, 0.0f),
      const Vector<float, 3> &palmRotation = Vector<float, 3>(0.0f, 0.0f, 0.0f),
      float confidence = 1.0f);

  int getHandIndex(void) const;
  const Vector<float, 3> &getPalmPosition(void) const;
  const Vector<float, 3> &getPalmRotation(void) const;
  float getConfidence(void) const;
};

/**
 * @brief Head pose event class for VR/AR head tracking
 */
class HeadPoseEvent : public Event {
private:
  Vector<float, 3> _position;
  Vector<float, 3> _rotation;

public:
  /**
   * @brief Construct a head pose event
   *
   * @param position The 3D position of the head
   * @param rotation The 3D rotation (Euler angles) of the head
   */
  HeadPoseEvent(const Vector<float, 3> &position,
                const Vector<float, 3> &rotation);

  const Vector<float, 3> &getPosition(void) const;
  const Vector<float, 3> &getRotation(void) const;
};

/**
 * @brief Gesture event class for AR/VR gestures
 */
class GestureEvent : public Event {
private:
  Vector<float, 2> _startPosition;
  Vector<float, 2> _endPosition;
  float _intensity;

public:
  /**
   * @brief Construct a gesture event
   *
   * @param type The type of gesture
   * @param startPosition The starting position
   * @param endPosition The ending position
   * @param intensity The intensity/magnitude of the gesture
   */
  GestureEvent(EventType type, const Vector<float, 2> &startPosition,
               const Vector<float, 2> &endPosition, float intensity = 1.0f);

  const Vector<float, 2> &getStartPosition(void) const;
  const Vector<float, 2> &getEndPosition(void) const;
  float getIntensity(void) const;
};

/**
 * @brief Stream insertion operator for Event
 */
std::ostream &operator<<(std::ostream &os, const Event &event);

} // namespace utility

#include <iostream>