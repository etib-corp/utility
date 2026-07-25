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
#include <vector>
#include <string>

#include "utility/event/event.hpp"

namespace utility::event
{

	/**
	 * @brief File drop event.
	 *
	 * Represents files and/or directories dropped on a window.
	 * This event is triggered when the user drops files on the window,
	 * typically from the file system or another application.
	 */
	class FileDropEvent: public Event
	{
		public:
		/**
		 * @brief Factory for creating FileDropEvent instances.
		 */
		class Factory: public Event::AbstractFactory
		{
			public:
			~Factory(void) override;

			/**
			 * @brief Create a FileDropEvent as a base Event pointer.
			 * @return Newly created FileDropEvent as std::shared_ptr<Event>.
			 */
			std::shared_ptr<Event> create(void) const override;

			/**
			 * @brief Create a strongly-typed FileDropEvent.
			 * @return Newly created FileDropEvent as
			 * std::shared_ptr<FileDropEvent>.
			 */
			std::shared_ptr<FileDropEvent> createTyped(void) const;
		};

		private:
		std::vector<std::string> _paths {}; /**< Paths of dropped files/dirs */

		public:
		/**
		 * @brief Default constructor.
		 */
		explicit FileDropEvent(void);

		/**
		 * @brief Default destructor.
		 */
		~FileDropEvent(void) override;

		/**
		 * @brief Set the paths of dropped files/directories.
		 * @param paths The UTF-8 encoded paths of dropped items.
		 * @return Reference to this FileDropEvent for method chaining.
		 */
		FileDropEvent &setPaths(const std::vector<std::string> &paths);

		/**
		 * @brief Get the paths of dropped files/directories.
		 * @return A vector of UTF-8 encoded paths.
		 */
		const std::vector<std::string> &getPaths(void) const noexcept;

		/**
		 * @brief Get the number of dropped items.
		 * @return The count of dropped files/directories.
		 */
		std::size_t getCount(void) const noexcept;
	};

}	 // namespace utility::event
