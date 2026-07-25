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

#ifdef __ANDROID__

	#include <android/asset_manager.h>
	#include <android/asset_manager_jni.h>

	#include "utility/system_io/system_io.hpp"

	#include <utility/logging/loggable.hpp>
	#include <utility/logging/default_logger.hpp>

namespace utility
{

	/**
	 * @class AndroidSystemIO
	 * @brief The AndroidSystemIO class is an implementation of SystemIO
	 * that uses the Android NDK's AAssetManager to load assets from the APK.
	 */
	class AndroidSystemIO:
		public SystemIO,
		protected utility::logging::Loggable<AndroidSystemIO,
											 utility::logging::DefaultLogger>
	{
		private:
		AAssetManager
			*_assetManager; /**< Pointer to the Android asset manager */

		public:
		/**
		 * @brief Constructs an AndroidSystemIO with the given
		 * AAssetManager.
		 * @param systemInterface The AAssetManager to use for loading assets.
		 */
		explicit AndroidSystemIO(AAssetManager *systemInterface);

		/**
		 * @brief Default destructor for AndroidSystemIO.
		 */
		~AndroidSystemIO() override = default;

		/**
		 * @brief Loads assets from a directory in the APK.
		 * @param directory The path to the directory in the APK containing the
		 * assets.
		 * @return True if the assets were loaded successfully, false otherwise.
		 */
		bool loadDirectory(const std::string &directory) override;

		/**
		 * @brief Loads an asset from the APK.
		 * @param path The path to the asset in the APK.
		 * @return A shared pointer to the loaded File, or nullptr if
		 * loading failed.
		 */
		std::shared_ptr<utility::File> add(const std::string &path) override;

		/**
		 * @brief Removes an asset from the manager.
		 * @param path The path to the asset to remove.
		 * @param save Whether to save the asset before removing it (not
		 * applicable for Android assets).
		 */
		void remove(const std::string &path, bool save = true) override;

		/**
		 * @brief Saves an asset (not applicable for Android assets).
		 * @param path The path to the asset to save.
		 * @param newPath An optional new path to save the asset to (not
		 * applicable for Android assets).
		 * @return Always returns false since saving is not supported for
		 * Android assets.
		 */
		bool save(const std::string &path,
				  const std::string &newPath = "") override;

		using Loggable::getLogger;
	};
}	 // namespace utility

#endif	  // __ANDROID__
