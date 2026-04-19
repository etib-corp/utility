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
 * @brief Hand thumbstick event.
 */
class HandThumbStickEvent : public HandEvent {
public:
	/**
	 * @brief Factory for creating HandThumbStickEvent instances.
	 */
	class Factory : public Event::AbstractFactory {
	public:
		~Factory(void) override;

		/**
		 * @brief Create a HandThumbStickEvent as base Event pointer.
		 * @return Newly created HandThumbStickEvent.
		 */
		std::unique_ptr<Event> create(void) const override;

		/**
		 * @brief Create a strongly-typed HandThumbStickEvent.
		 * @return Newly created HandThumbStickEvent.
		 */
		std::unique_ptr<HandThumbStickEvent> createTyped(void) const;
	};

private:
	/** @brief X axis value in range [-1, 1]. */
	float _x{0.0F};

	/** @brief Y axis value in range [-1, 1]. */
	float _y{0.0F};

	/** @brief True when the thumbstick surface is touched. */
	bool _isTouched{false};

	/** @brief True when the thumbstick is clicked. */
	bool _isClicked{false};

public:
	/**
	 * @brief Default constructor.
	 */
	explicit HandThumbStickEvent(void);
	~HandThumbStickEvent(void) override;

	/**
	 * @brief Set X axis value.
	 * @param x Axis value.
	 * @return Reference to this HandThumbStickEvent.
	 */
	HandThumbStickEvent &setX(const float x) noexcept;

	/**
	 * @brief Get X axis value.
	 * @return Axis value in [-1, 1].
	 */
	float getX(void) const noexcept;

	/**
	 * @brief Set Y axis value.
	 * @param y Axis value.
	 * @return Reference to this HandThumbStickEvent.
	 */
	HandThumbStickEvent &setY(const float y) noexcept;

	/**
	 * @brief Get Y axis value.
	 * @return Axis value in [-1, 1].
	 */
	float getY(void) const noexcept;

	/**
	 * @brief Set both axis values.
	 * @param x X axis value.
	 * @param y Y axis value.
	 * @return Reference to this HandThumbStickEvent.
	 */
	HandThumbStickEvent &setAxis(const float x, const float y) noexcept;

	/**
	 * @brief Set touched state.
	 * @param touched True if touched.
	 * @return Reference to this HandThumbStickEvent.
	 */
	HandThumbStickEvent &setTouched(const bool touched) noexcept;

	/**
	 * @brief Get touched state.
	 * @return True if touched.
	 */
	bool isTouched(void) const noexcept;

	/**
	 * @brief Set clicked state.
	 * @param clicked True if clicked.
	 * @return Reference to this HandThumbStickEvent.
	 */
	HandThumbStickEvent &setClicked(const bool clicked) noexcept;

	/**
	 * @brief Get clicked state.
	 * @return True if clicked.
	 */
	bool isClicked(void) const noexcept;
};

} // namespace utility::event
