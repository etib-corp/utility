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
#include "utility/sound/decoder/decoder_registry.hpp"

#include <utility/logging/default_logger.hpp>

namespace utility::sound
{
	static utility::logging::DefaultLogger
		decoderRegistryLogger("DecoderRegistry");
}

std::shared_ptr<utility::sound::AAudioDecoder>
	utility::sound::DecoderRegistry::getDecoderForFile(
		const std::string &filePath, AudioDecoderType type)
{
	/**
	 * This is a simple implementation that checks each decoder in the
	 * registry to see if it can decode the given file path or type. In a
	 * more complex implementation, you might want to use a more efficient
	 * lookup mechanism, such as a map of file extensions to decoders, or a
	 * plugin system for dynamically loading decoders.
	 *
	 */
	static const std::vector<std::shared_ptr<AAudioDecoder>> decoders = {
		std::make_shared<WAVDecoder>(), std::make_shared<MP3Decoder>()
	};
	for (const auto &decoder: decoders) {
		if (decoder->canDecode(filePath) || decoder->canDecode(type)) {
			decoderRegistryLogger.debug()
				<< "Found decoder for file: " << filePath;
			return decoder;
		}
	}
	decoderRegistryLogger.warning()
		<< "No decoder found for file: " << filePath;
	return nullptr;
}
