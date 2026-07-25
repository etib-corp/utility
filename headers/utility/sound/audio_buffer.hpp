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

#include <AL/al.h>
#include <AL/alc.h>

#include "utility/sound/decoder/audio_decoder.hpp"

namespace utility::sound
{
	/**
	 * @brief Wrapper around an OpenAL audio buffer.
	 *
	 * AudioBuffer manages the lifetime of an OpenAL buffer object and
	 * provides a simple interface for uploading decoded PCM audio data.
	 *
	 * The buffer is automatically released when the instance is destroyed.
	 */
	class AudioBuffer
	{
		public:
		/**
		 * @brief Creates an empty audio buffer.
		 *
		 * No OpenAL resource is allocated until upload() is called.
		 */
		AudioBuffer();

		/**
		 * @brief Destroys the audio buffer and releases its OpenAL resource.
		 */
		~AudioBuffer();

		/**
		 * @brief Retrieves the underlying OpenAL buffer identifier.
		 *
		 * @return The OpenAL buffer handle, or 0 if no buffer has been created.
		 */
		[[nodiscard]] ALuint bufferID() const;

		/**
		 * @brief Uploads decoded audio data to the OpenAL buffer.
		 *
		 * If a buffer already exists, it is deleted and recreated before
		 * uploading the new data.
		 *
		 * @param decodedAudio Decoded PCM audio data and associated format
		 * information.
		 */
		void upload(const DecodedAudio &decodedAudio);

		private:
		/**
		 * @brief OpenAL buffer handle.
		 */
		ALuint _bufferID = 0;
	};
}	 // namespace utility::sound