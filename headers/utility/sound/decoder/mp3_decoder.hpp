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

#include "utility/sound/decoder/audio_decoder.hpp"
#include "utility/sound/audio_buffer.hpp"

namespace utility::sound
{
	/**
	 * @class MP3Decoder
	 *
	 * @brief Decoder implementation for MPEG Audio Layer III (MP3) files.
	 *
	 * MP3Decoder uses the dr_mp3 library to decode MP3-encoded audio data
	 * into raw Pulse-Code Modulation (PCM) samples compatible with OpenAL.
	 *
	 * Decoded audio samples are converted to 16-bit PCM format and uploaded
	 * to an AudioBuffer instance for playback.
	 */
	class MP3Decoder: public AAudioDecoder
	{
		public:
		/**
		 * @brief Creates an MP3 decoder instance.
		 */
		MP3Decoder();

		/**
		 * @brief Destroys the MP3 decoder instance.
		 */
		~MP3Decoder() override;

		/**
		 * @brief Determines whether the specified file can be decoded.
		 *
		 * Compatibility is determined from the file extension.
		 *
		 * @param filePath Path to the audio file.
		 *
		 * @return true if the file extension is supported, false otherwise.
		 */
		bool canDecode(const std::string &filePath) const override;

		/**
		 * @brief Determines whether the specified decoder type is supported.
		 *
		 * @param type Audio decoder type to test.
		 *
		 * @return true if the decoder supports the specified type, false
		 * otherwise.
		 */
		bool canDecode(AudioDecoderType type) const override;

		/**
		 * @brief Decodes an MP3 file into an AudioBuffer.
		 *
		 * The encoded audio stream is decoded into 16-bit PCM samples and
		 * uploaded to an AudioBuffer for playback.
		 *
		 * @param file The file containing MP3-encoded audio data.
		 *
		 * @return A shared pointer to the decoded AudioBuffer, or nullptr if
		 * decoding fails.
		 */
		[[nodiscard]]
		std::shared_ptr<AudioBuffer>
			decode(std::shared_ptr<utility::File> file) override;
	};
}	 // namespace utility::sound