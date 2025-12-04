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

#include "Event.hpp"

namespace utility {

// Base Event class

Event::Event(EventType type) : _type(type) {
  _timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
}

EventType Event::getType(void) const { return _type; }

uint64_t Event::getTimestamp(void) const { return _timestamp; }

bool Event::isType(EventType type) const { return _type == type; }

// KeyboardEvent

KeyboardEvent::KeyboardEvent(EventType type, int keyCode, KeyModifier modifiers)
    : Event(type), _keyCode(keyCode), _modifiers(modifiers) {}

int KeyboardEvent::getKeyCode(void) const { return _keyCode; }

KeyModifier KeyboardEvent::getModifiers(void) const { return _modifiers; }

// MouseEvent

MouseEvent::MouseEvent(EventType type, const Vector<float, 2> &position,
                       const Vector<float, 2> &delta, MouseButton button,
                       KeyModifier modifiers)
    : Event(type), _position(position), _delta(delta), _button(button),
      _modifiers(modifiers) {}

const Vector<float, 2> &MouseEvent::getPosition(void) const {
  return _position;
}

const Vector<float, 2> &MouseEvent::getDelta(void) const { return _delta; }

MouseButton MouseEvent::getButton(void) const { return _button; }

KeyModifier MouseEvent::getModifiers(void) const { return _modifiers; }

// TouchEvent

TouchEvent::TouchEvent(EventType type, const Vector<float, 2> &position,
                       float pressure, uint32_t touchId, int touchCount)
    : Event(type), _position(position), _pressure(pressure), _touchId(touchId),
      _touchCount(touchCount) {}

const Vector<float, 2> &TouchEvent::getPosition(void) const {
  return _position;
}

float TouchEvent::getPressure(void) const { return _pressure; }

uint32_t TouchEvent::getTouchId(void) const { return _touchId; }

int TouchEvent::getTouchCount(void) const { return _touchCount; }

// ControllerEvent

ControllerEvent::ControllerEvent(EventType type, int controllerIndex,
                                 float axisValue,
                                 const Vector<float, 3> &position,
                                 const Vector<float, 3> &rotation)
    : Event(type), _controllerIndex(controllerIndex), _axisValue(axisValue),
      _position(position), _rotation(rotation) {}

int ControllerEvent::getControllerIndex(void) const { return _controllerIndex; }

float ControllerEvent::getAxisValue(void) const { return _axisValue; }

const Vector<float, 3> &ControllerEvent::getPosition(void) const {
  return _position;
}

const Vector<float, 3> &ControllerEvent::getRotation(void) const {
  return _rotation;
}

// HandTrackingEvent

HandTrackingEvent::HandTrackingEvent(EventType type, int handIndex,
                                     const Vector<float, 3> &palmPosition,
                                     const Vector<float, 3> &palmRotation,
                                     float confidence)
    : Event(type), _handIndex(handIndex), _palmPosition(palmPosition),
      _palmRotation(palmRotation), _confidence(confidence) {}

int HandTrackingEvent::getHandIndex(void) const { return _handIndex; }

const Vector<float, 3> &HandTrackingEvent::getPalmPosition(void) const {
  return _palmPosition;
}

const Vector<float, 3> &HandTrackingEvent::getPalmRotation(void) const {
  return _palmRotation;
}

float HandTrackingEvent::getConfidence(void) const { return _confidence; }

// HeadPoseEvent

HeadPoseEvent::HeadPoseEvent(const Vector<float, 3> &position,
                             const Vector<float, 3> &rotation)
    : Event(EventType::HeadPoseUpdate), _position(position),
      _rotation(rotation) {}

const Vector<float, 3> &HeadPoseEvent::getPosition(void) const {
  return _position;
}

const Vector<float, 3> &HeadPoseEvent::getRotation(void) const {
  return _rotation;
}

// GestureEvent

GestureEvent::GestureEvent(EventType type,
                           const Vector<float, 2> &startPosition,
                           const Vector<float, 2> &endPosition, float intensity)
    : Event(type), _startPosition(startPosition), _endPosition(endPosition),
      _intensity(intensity) {}

const Vector<float, 2> &GestureEvent::getStartPosition(void) const {
  return _startPosition;
}

const Vector<float, 2> &GestureEvent::getEndPosition(void) const {
  return _endPosition;
}

float GestureEvent::getIntensity(void) const { return _intensity; }

// Helper function to convert EventType to string
static const char *eventTypeToString(EventType type) {
  switch (type) {
  case EventType::KeyPress:
    return "KeyPress";
  case EventType::KeyRelease:
    return "KeyRelease";
  case EventType::MouseMove:
    return "MouseMove";
  case EventType::MouseButtonPress:
    return "MouseButtonPress";
  case EventType::MouseButtonRelease:
    return "MouseButtonRelease";
  case EventType::MouseScroll:
    return "MouseScroll";
  case EventType::TouchBegin:
    return "TouchBegin";
  case EventType::TouchMove:
    return "TouchMove";
  case EventType::TouchEnd:
    return "TouchEnd";
  case EventType::TouchCancel:
    return "TouchCancel";
  case EventType::ControllerButtonPress:
    return "ControllerButtonPress";
  case EventType::ControllerButtonRelease:
    return "ControllerButtonRelease";
  case EventType::ControllerAxisMotion:
    return "ControllerAxisMotion";
  case EventType::ControllerTrigger:
    return "ControllerTrigger";
  case EventType::ControllerGrip:
    return "ControllerGrip";
  case EventType::HandTrackingUpdate:
    return "HandTrackingUpdate";
  case EventType::GestureSwipe:
    return "GestureSwipe";
  case EventType::GesturePinch:
    return "GesturePinch";
  case EventType::GestureRotate:
    return "GestureRotate";
  case EventType::HeadPoseUpdate:
    return "HeadPoseUpdate";
  case EventType::EyeGazeUpdate:
    return "EyeGazeUpdate";
  case EventType::WindowClose:
    return "WindowClose";
  case EventType::WindowResize:
    return "WindowResize";
  case EventType::WindowFocus:
    return "WindowFocus";
  case EventType::WindowBlur:
    return "WindowBlur";
  case EventType::ApplicationPause:
    return "ApplicationPause";
  case EventType::ApplicationResume:
    return "ApplicationResume";
  case EventType::PlaneDetected:
    return "PlaneDetected";
  case EventType::PlaneUpdated:
    return "PlaneUpdated";
  case EventType::ImageTracked:
    return "ImageTracked";
  case EventType::FaceDetected:
    return "FaceDetected";
  case EventType::ObjectDetected:
    return "ObjectDetected";
  case EventType::Custom:
    return "Custom";
  default:
    return "Unknown";
  }
}

std::ostream &operator<<(std::ostream &os, const Event &event) {
  os << "Event(" << eventTypeToString(event.getType())
     << ", Timestamp:" << event.getTimestamp() << ")";
  return os;
}

} // namespace utility