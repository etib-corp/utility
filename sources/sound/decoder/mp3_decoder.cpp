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
#define DR_MP3_IMPLEMENTATION
#include <dr_mp3.h>
#include "utility/sound/decoder/mp3_decoder.hpp"

#include <utility/logging/default_logger.hpp>

namespace utility::sound
{
	static utility::logging::DefaultLogger mp3DecoderLogger("MP3Decoder");
}

utility::sound::MP3Decoder::MP3Decoder()
{
	mp3DecoderLogger.debug() << "MP3 decoder initialized";
}

utility::sound::MP3Decoder::~MP3Decoder()
{
	mp3DecoderLogger.debug() << "MP3 decoder destroyed";
}

bool utility::sound::MP3Decoder::canDecode(const std::string &filePath) const
{
	// Check if the file extension is .mp3
	auto extension = filePath.substr(filePath.find_last_of(".") + 1);
	return extension == "mp3";
}

bool utility::sound::MP3Decoder::canDecode(AudioDecoderType type) const
{
	return type == AudioDecoderType::MP3;
}

std::shared_ptr<utility::sound::AudioBuffer>
	utility::sound::MP3Decoder::decode(std::shared_ptr<utility::File> file)
{
	auto audioBuffer = std::make_shared<AudioBuffer>();
	DecodedAudio decodedAudio;
	drmp3 mp3 = {};

	if (drmp3_init_memory(&mp3, file->content().data(), file->size(), nullptr)
		== DRMP3_FALSE) {
		// Log error but don't throw - return nullptr
		return nullptr;
	}

	const drmp3_uint64 frameCount = drmp3_get_pcm_frame_count(&mp3);
	if (frameCount == 0) {
		drmp3_uninit(&mp3);
		return nullptr;
	}
	decodedAudio.sampleRate	   = mp3.sampleRate;
	decodedAudio.channels	   = mp3.channels;
	decodedAudio.bitsPerSample = 16;

	decodedAudio.format =
		getALFormat(decodedAudio.channels, decodedAudio.bitsPerSample);

	const size_t totalSampleCount = frameCount * mp3.channels;

	std::vector<drmp3_int16> pcm(totalSampleCount);

	const drmp3_uint64 samplesDecoded =
		drmp3_read_pcm_frames_s16(&mp3, frameCount, pcm.data());

	drmp3_uninit(&mp3);

	if (samplesDecoded == 0) {
		return nullptr;
	}
	decodedAudio.samples.resize(samplesDecoded * mp3.channels
								* sizeof(drmp3_int16));
	std::memcpy(decodedAudio.samples.data(), pcm.data(),
				decodedAudio.samples.size());

	audioBuffer->upload(decodedAudio);
	return audioBuffer;
}
