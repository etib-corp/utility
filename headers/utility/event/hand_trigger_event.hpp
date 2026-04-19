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

#pragma once

#include <memory>

#include "utility/event/hand_event.hpp"

namespace utility::event {

/**
 * @brief Hand trigger event.
 */
class HandTriggerEvent : public HandEvent {
public:
	/**
	 * @brief Factory for creating HandTriggerEvent instances.
	 */
	class Factory : public Event::AbstractFactory {
	public:
		~Factory(void) override;

		/**
		 * @brief Create a HandTriggerEvent as base Event pointer.
		 * @return Newly created HandTriggerEvent.
		 */
		std::unique_ptr<Event> create(void) const override;

		/**
		 * @brief Create a strongly-typed HandTriggerEvent.
		 * @return Newly created HandTriggerEvent.
		 */
		std::unique_ptr<HandTriggerEvent> createTyped(void) const;
	};

private:
	/** @brief Trigger value in range [0, 1]. */
	float _value{0.0F};

	/** @brief True when trigger is touched. */
	bool _isTouched{false};

	/** @brief True when finger is in trigger proximity region. */
	bool _isProximity{false};

public:
	/**
	 * @brief Default constructor.
	 */
	explicit HandTriggerEvent(void);
	~HandTriggerEvent(void) override;

	/**
	 * @brief Set trigger value.
	 * @param value Trigger value.
	 * @return Reference to this HandTriggerEvent.
	 */
	HandTriggerEvent &setValue(const float value) noexcept;

	/**
	 * @brief Get trigger value.
	 * @return Value in [0, 1].
	 */
	float getValue(void) const noexcept;

	/**
	 * @brief Set touched state.
	 * @param touched True if touched.
	 * @return Reference to this HandTriggerEvent.
	 */
	HandTriggerEvent &setTouched(const bool touched) noexcept;

	/**
	 * @brief Get touched state.
	 * @return True if touched.
	 */
	bool isTouched(void) const noexcept;

	/**
	 * @brief Set proximity state.
	 * @param proximity True if in proximity.
	 * @return Reference to this HandTriggerEvent.
	 */
	HandTriggerEvent &setProximity(const bool proximity) noexcept;

	/**
	 * @brief Get proximity state.
	 * @return True if in proximity.
	 */
	bool isProximity(void) const noexcept;
};

} // namespace utility::event
