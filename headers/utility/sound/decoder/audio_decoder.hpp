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

#include <iostream>
#include <vector>

#include "utility/system_io/file.hpp"

namespace utility::sound
{
	class AudioBuffer;

	/**
	 * @struct DecodedAudio
	 *
	 * @brief Contains decoded Pulse-Code Modulation (PCM) audio data.
	 *
	 * This structure stores raw audio samples together with the metadata
	 * required to upload them to an OpenAL buffer.
	 *
	 * Instances of this structure are typically produced by implementations
	 * of AAudioDecoder during the decoding process.
	 */
	struct DecodedAudio {
		/**
		 * @brief Raw PCM sample data.
		 */
		std::vector<std::byte> samples;

		/**
		 * @brief Audio sample rate in hertz.
		 */
		uint32_t sampleRate = 0;

		/**
		 * @brief Number of audio channels.
		 *
		 * Typical values are:
		 * - 1 for mono
		 * - 2 for stereo
		 */
		uint16_t channels = 0;

		/**
		 * @brief Number of bits used to represent each sample.
		 *
		 * Typical values are 8 or 16.
		 */
		uint16_t bitsPerSample = 0;

		/**
		 * @brief OpenAL format corresponding to the decoded audio data.
		 *
		 * The value is typically obtained using
		 * AAudioDecoder::getALFormat().
		 */
		ALenum format = 0;
	};

	/**
	 * @enum AudioDecoderType
	 *
	 * @brief Enumerates the supported audio decoder types.
	 */
	enum class AudioDecoderType {
		/**
		 * @brief Waveform Audio File Format.
		 */
		WAV,

		/**
		 * @brief MPEG Audio Layer III.
		 */
		MP3,

		/**
		 * @brief Unknown or unspecified audio format.
		 */
		UNKNOWN
	};

	/**
	 * @class AAudioDecoder
	 *
	 * @brief Abstract base class for audio decoders.
	 *
	 * This class defines the common interface for decoding audio files into
	 * AudioBuffer objects that can be played through the audio subsystem.
	 *
	 * Concrete implementations are responsible for:
	 * - Detecting whether they support a specific audio format
	 * - Reading and decoding audio data from files
	 * - Converting decoded samples to a format compatible with OpenAL
	 * - Creating and populating AudioBuffer instances
	 *
	 * Supported formats are identified either by file path or by
	 * AudioDecoderType.
	 */
	class AAudioDecoder
	{
		public:
		/**
		 * @brief Virtual destructor.
		 */
		virtual ~AAudioDecoder() = default;

		/**
		 * @brief Determines whether the decoder supports the specified file.
		 *
		 * Implementations typically inspect the file extension or file
		 * contents to determine compatibility.
		 *
		 * @param filePath Path to the audio file.
		 *
		 * @return true if the decoder supports the specified file, false
		 * otherwise.
		 */
		virtual bool canDecode(const std::string &filePath) const = 0;

		/**
		 * @brief Determines whether the decoder supports the specified audio
		 * type.
		 *
		 * @param type The audio format to test.
		 *
		 * @return true if the decoder supports the specified type, false
		 * otherwise.
		 */
		virtual bool canDecode(
			AudioDecoderType type = AudioDecoderType::UNKNOWN) const = 0;

		/**
		 * @brief Decodes an audio file into an AudioBuffer.
		 *
		 * This function reads the specified file, decodes its audio content,
		 * uploads the decoded samples to an AudioBuffer, and returns the
		 * resulting buffer.
		 *
		 * @param file The file containing the encoded audio data.
		 *
		 * @return A shared pointer to the decoded AudioBuffer.
		 *
		 * @throws std::runtime_error If decoding fails or the file format is
		 * invalid.
		 */
		virtual std::shared_ptr<AudioBuffer>
			decode(std::shared_ptr<utility::File> file) = 0;

		/**
		 * @brief Converts audio properties to an OpenAL format.
		 *
		 * This helper function maps the specified channel count and sample
		 * size to the corresponding OpenAL format enumeration.
		 *
		 * @param channels Number of audio channels.
		 * @param bitsPerSample Number of bits per sample.
		 *
		 * @return The corresponding OpenAL format.
		 *
		 * @throws std::runtime_error If the specified format is unsupported.
		 */
		ALenum getALFormat(uint16_t channels, uint16_t bitsPerSample) const;
	};
}	 // namespace utility::sound