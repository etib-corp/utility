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
#include "utility/sound/decoder/wav_decoder.hpp"

#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

#include <utility/logging/default_logger.hpp>

namespace utility::sound
{
	static utility::logging::DefaultLogger wavDecoderLogger("WAVDecoder");
}

utility::sound::WAVDecoder::WAVDecoder()
{
	wavDecoderLogger.debug() << "WAV decoder initialized";
}

utility::sound::WAVDecoder::~WAVDecoder()
{
	wavDecoderLogger.debug() << "WAV decoder destroyed";
}

bool utility::sound::WAVDecoder::canDecode(const std::string &filePath) const
{
	// Check if the file extension is .wav
	auto extension = filePath.substr(filePath.find_last_of(".") + 1);
	return extension == "wav";
}

bool utility::sound::WAVDecoder::canDecode(AudioDecoderType type) const
{
	return type == AudioDecoderType::WAV;
}

std::shared_ptr<utility::sound::AudioBuffer>
	utility::sound::WAVDecoder::decode(std::shared_ptr<utility::File> file)
{
	auto audioBuffer = std::make_shared<AudioBuffer>();
	DecodedAudio decodedAudio;

	drwav wav;
	if (!drwav_init_memory(&wav, file->content().data(), file->size(),
						   nullptr)) {
		// Failed to initialize the WAV decoder. Return nullptr.
		return nullptr;
	}

	decodedAudio.channels	   = wav.channels;
	decodedAudio.sampleRate	   = wav.sampleRate;
	decodedAudio.bitsPerSample = wav.bitsPerSample;
	decodedAudio.samples.resize(
		static_cast<size_t>(wav.totalPCMFrameCount * wav.channels));

	size_t framesRead = drwav_read_pcm_frames(&wav, wav.totalPCMFrameCount,
											  decodedAudio.samples.data());
	if (framesRead != wav.totalPCMFrameCount) {
		drwav_uninit(&wav);
		return nullptr;
	}

	decodedAudio.format =
		getALFormat(decodedAudio.channels, decodedAudio.bitsPerSample);

	drwav_uninit(&wav);
	audioBuffer->upload(decodedAudio);
	return audioBuffer;
}
