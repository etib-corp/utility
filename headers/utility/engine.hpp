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

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>

#include <utility/logging/loggable.hpp>
#include <utility/logging/default_logger.hpp>

#include <utility/graphic/view.hpp>
#include <utility/graphic/mesh.hpp>
#include <utility/graphic/model.hpp>
#include <utility/graphic/scissor.hpp>
#include <utility/graphic/size.hpp>
#include <utility/graphic/text/text.hpp>

#include <utility/math/vector.hpp>

#include <utility/event/event.hpp>

namespace utility
{

	/**
	 * @brief Engine interface combining rendering and event handling.
	 *
	 * This class provides an abstract interface for the core engine loop.
	 * Implementations should provide platform-specific rendering and event
	 * polling capabilities.
	 *
	 * @code
	 * class MyEngine : public Engine { ... };
	 * @endcode
	 */
	class Engine:
		protected utility::logging::Loggable<Engine,
											 utility::logging::DefaultLogger>
	{
		public:
		/**
		 * @brief 2D vector representing viewport width and height in pixels.
		 */
		using ViewportSize = utility::math::Vector2F;

		/**
		 * @brief Type alias for an event handler callback function.
		 *
		 * Takes a shared pointer to an Event and performs an action.
		 */
		using Handler =
			std::function<void(std::shared_ptr<utility::event::Event> &)>;

		private:
		Handler _callback;	  ///< Event callback function
		bool _shouldCaptureViewportInput {
			true
		};	  ///< Viewport input capture state
		std::optional<utility::graphic::ScissorRect> _scissor {
			std::nullopt
		};	  ///< Active scissor rectangle

		protected:
		/**
		 * @brief Get the current event callback function.
		 * @return Reference to the event callback function.
		 */
		Handler &getEventCallback(void);

		public:
		/**
		 * @brief Check if viewport input capture is enabled.
		 * @return True when viewport input is captured for camera movement.
		 */
		bool shouldCaptureViewportInput(void) const;

		/**
		 * @brief Set the viewport input capture state.
		 * @param capture True to enable viewport input capture, false to
		 * disable. When disabled, input is routed to UI instead of camera
		 * controls.
		 */
		void setShouldCaptureViewportInput(bool capture);

		public:
		/**
		 * @brief Default constructor
		 */
		Engine(void);

		/**
		 * @brief Default destructor
		 */
		virtual ~Engine(void) = default;

		public:
		/**
		 * @brief Clear the current rendering target with the drawing color.
		 */
		virtual void clear(void) = 0;

		/**
		 * @brief Present the composed back buffer to the screen.
		 */
		virtual void present(void) = 0;

		/**
		 * @brief Measures the pixel dimensions of a given text string when
		 * rendered with a specific font.
		 * @param text The text to measure.
		 * @return A 2D vector containing the width and height of the rendered
		 * text in pixels in the form of utility::math::Vector2F.
		 */
		virtual utility::graphic::SizeF
			measureText(const utility::graphic::Text &text) const = 0;

		/**
		 * @brief Create a new render object.
		 *
		 * @param object A shared pointer to the renderable object to create.
		 * @return A unique identifier for the created object.
		 */
		virtual size_t createObject(
			std::shared_ptr<utility::graphic::Renderable> object) = 0;

		/**
		 * @brief Update a previously added render object.
		 *
		 * @param object The updated renderable object.
		 * @param objectID The identifier returned by createObject.
		 * @return True when the object was updated.
		 */
		virtual bool
			updateObject(std::shared_ptr<utility::graphic::Renderable> object,
						 size_t objectID) = 0;

		/**
		 * @brief Remove a previously added render object.
		 *
		 * @param object The renderable object to remove.
		 * @param objectID The identifier returned by createObject.
		 * @return True when the object was removed.
		 */
		virtual bool
			removeObject(std::shared_ptr<utility::graphic::Renderable> object,
						 size_t objectID) = 0;

		/**
		 * @brief Get the full view model.
		 * @return The view instance.
		 */
		virtual utility::graphic::ViewF getView(void) const = 0;

		/**
		 * @brief Get the time elapsed since the previous frame.
		 *
		 * Implementations backed by a real clock should override this so that
		 * time-based systems (animations, transitions) advance with the
		 * platform frame rate. The default returns 0, in which case callers
		 * fall back to their own monotonic clock.
		 *
		 * @return Delta time in seconds.
		 */
		virtual float getDeltaTime(void) const;

		/**
		 * @brief Set the active scissor (clip) rectangle.
		 *
		 * The rectangle is expressed in framebuffer pixels. Implementations
		 * backed by a renderer should clip subsequent draws to it; the base
		 * implementation only stores the rectangle so it can be queried with
		 * getScissor().
		 *
		 * @param rect The scissor rectangle to apply.
		 */
		virtual void setScissor(const utility::graphic::ScissorRect &rect);

		/**
		 * @brief Clear the active scissor (clip) rectangle.
		 */
		virtual void clearScissor(void);

		/**
		 * @brief Get the active scissor (clip) rectangle.
		 * @return The active rectangle, or std::nullopt when none is set.
		 */
		std::optional<utility::graphic::ScissorRect> getScissor(void) const;

		/**
		 * @brief Set the event callback function.
		 *
		 * The callback will be invoked for each event when pollEvents() is
		 * called.
		 *
		 * @param callback Function to call when an event is received.
		 */
		void setEventCallback(const Handler &callback);

		/**
		 * @brief Poll for events and dispatch them.
		 *
		 * This method should check for pending events from the underlying
		 * platform, convert them to Event objects, and call the registered
		 * callback for each event.
		 */
		virtual void pollEvents(void) = 0;

		/**
		 * @brief Update the engine state.
		 *
		 * This method should handle logic updates, input processing, and other
		 * non-rendering related tasks. It is typically called once per frame,
		 * allowing the engine to respond to user input and update the state of
		 * objects in the renderer.
		 */
		virtual void update(void) = 0;
	};

	/**
	 * @brief Concept to ensure a type inherits from Engine.
	 * @tparam Type The type to check.
	 */
	template<typename Type>
	concept InheritFromEngine = std::is_base_of_v<Engine, Type>;

}	 // namespace utility
