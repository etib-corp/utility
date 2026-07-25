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

#include "utility/sound/decoder/mp3_decoder.hpp"
#include "utility/sound/decoder/wav_decoder.hpp"

namespace utility::sound
{
	/**
	 * @class DecoderRegistry
	 *
	 * @brief Factory responsible for resolving audio decoders.
	 *
	 * DecoderRegistry provides a centralized mechanism for locating an
	 * appropriate AAudioDecoder implementation for a given audio file or
	 * decoder type.
	 *
	 * The registry abstracts format-specific decoder selection from the rest
	 * of the audio subsystem, allowing clients to decode audio files without
	 * needing to know which concrete decoder implementation is required.
	 *
	 * Supported decoder implementations are evaluated sequentially until a
	 * compatible decoder is found.
	 *
	 * @note The current implementation uses a static collection of decoder
	 * instances.
	 *
	 * @note Future implementations may replace the linear search with a more
	 * efficient lookup mechanism or a plugin-based architecture.
	 */
	class DecoderRegistry
	{
		public:
		/**
		 * @brief Retrieves a decoder compatible with the specified audio
		 * source.
		 *
		 * The registry attempts to find a decoder that supports either the
		 * provided file path or the specified decoder type.
		 *
		 * @param filePath Path to the audio file.
		 * @param type Explicit audio type hint.
		 *
		 * @return A shared pointer to a compatible decoder, or nullptr if no
		 * suitable decoder is found.
		 */
		[[nodiscard]]
		static std::shared_ptr<AAudioDecoder> getDecoderForFile(
			const std::string &filePath,
			AudioDecoderType type = AudioDecoderType::UNKNOWN);

		private:
		DecoderRegistry()  = delete;
		~DecoderRegistry() = delete;
	};
}	 // namespace utility::sound