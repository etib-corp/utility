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

#include <cstdint>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utility/event/event.hpp"

namespace utility::event
{

	/**
	 * @brief Dispatches typed events to registered listeners.
	 *
	 * Listeners are registered per concrete event type. When an event is
	 * emitted, all listeners registered for that type are invoked with a
	 * strongly typed reference. Events are dispatched to the concrete type
	 * derived from the base Event pointer via a runtime type check.
	 *
	 * The dispatcher owns no events; it only forwards them. It is safe to
	 * register and emit from the same thread.
	 */
	class EventDispatcher
	{
		private:
		using Handler = std::function<void(const Event &)>;

		std::unordered_map<std::size_t, std::vector<Handler>> _handlers;

		template<typename EventType>
		static std::size_t typeKey(void) noexcept
		{
			static const EventType *marker = nullptr;
			return reinterpret_cast<std::size_t>(&marker);
		}

		public:
		/**
		 * @brief Default constructor.
		 */
		EventDispatcher(void) = default;

		/**
		 * @brief Default destructor.
		 */
		~EventDispatcher(void) = default;

		/**
		 * @brief Register a listener for a concrete event type.
		 * @tparam EventType The concrete event type (must derive from Event).
		 * @param listener Callable invoked with a const reference to the event.
		 * @note The listener is invoked synchronously on the emitting thread.
		 */
		template<InheritFromEvent EventType, typename Callable>
		void addListener(Callable &&listener)
		{
			auto key = typeKey<EventType>();
			_handlers[key].emplace_back(
				[fn = std::forward<Callable>(listener)](const Event &event) mutable {
					fn(static_cast<const EventType &>(event));
				});
		}

		/**
		 * @brief Emit an event to all listeners registered for its concrete
		 * type.
		 * @tparam EventType The concrete event type.
		 * @param event The event to dispatch.
		 */
		template<InheritFromEvent EventType>
		void emit(const EventType &event) const
		{
			auto key = typeKey<EventType>();
			auto it  = _handlers.find(key);
			if (it == _handlers.end()) {
				return;
			}
			for (const auto &handler: it->second) {
				handler(event);
			}
		}

		/**
		 * @brief Remove all listeners registered for a concrete event type.
		 * @tparam EventType The concrete event type.
		 */
		template<InheritFromEvent EventType>
		void clearListeners(void)
		{
			_handlers.erase(typeKey<EventType>());
		}

		/**
		 * @brief Remove all listeners for every event type.
		 */
		void clearAll(void) noexcept
		{
			_handlers.clear();
		}
	};

}	 // namespace utility::event
