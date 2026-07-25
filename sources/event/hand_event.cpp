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

#include "utility/event/hand_event.hpp"

namespace utility::event
{

	HandEvent::HandEvent(void) = default;

	HandEvent::~HandEvent(void) = default;

	HandEvent &HandEvent::setHandType(const HandType handType) noexcept
	{
		_handType = handType;
		return *this;
	}

	HandEvent::HandType HandEvent::getHandType(void) const noexcept
	{
		return _handType;
	}

	HandEvent &HandEvent::setPose(const graphic::PoseF &pose) noexcept
	{
		_pose = pose;
		return *this;
	}

	graphic::PoseF HandEvent::getPose(void) const noexcept
	{
		return _pose;
	}

	HandEvent &HandEvent::setAim(const graphic::PoseF &aim) noexcept
	{
		_aim = aim;
		return *this;
	}

	graphic::PoseF HandEvent::getAim(void) const noexcept
	{
		return _aim;
	}

	HandEvent &HandEvent::setGrip(const graphic::PoseF &grip) noexcept
	{
		_grip = grip;
		return *this;
	}

	graphic::PoseF HandEvent::getGrip(void) const noexcept
	{
		return _grip;
	}

	HandEvent &
		HandEvent::setGripSurface(const graphic::PoseF &gripSurface) noexcept
	{
		_gripSurface = gripSurface;
		return *this;
	}

	graphic::PoseF HandEvent::getGripSurface(void) const noexcept
	{
		return _gripSurface;
	}

	std::ostream &operator<<(std::ostream &stream,
							 const HandEvent::HandType handType)
	{
		switch (handType) {
			case HandEvent::HandType::Left:
				stream << "Left";
				break;
			case HandEvent::HandType::Right:
				stream << "Right";
				break;
			default:
				stream << "Unknown";
				break;
		}
		return stream;
	}
}	 // namespace utility::event