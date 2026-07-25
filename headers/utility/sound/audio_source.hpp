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

#include <memory>

#include "utility/sound/audio_buffer.hpp"

namespace utility::sound
{
	class AudioManager;

	/**
	 * @class AudioSource
	 *
	 * @brief Represents a playable audio source managed by AudioManager.
	 *
	 * This class provides a high-level interface for controlling audio
	 * playback, including starting, stopping, pausing, and modifying playback
	 * properties such as gain, pitch, and looping state.
	 *
	 * AudioSource instances do not interact with OpenAL directly. Instead,
	 * they submit commands to the associated AudioManager, which processes
	 * them asynchronously on a dedicated audio thread.
	 *
	 * An AudioSource owns a unique source identifier used by AudioManager to
	 * reference the underlying OpenAL source object.
	 *
	 * @note Destroying an AudioSource automatically releases its associated
	 * OpenAL source through AudioManager.
	 */
	class AudioSource
	{
		public:
		/**
		 * @brief Creates a new audio source.
		 *
		 * @param sourceID Unique identifier assigned by AudioManager.
		 * @param manager Reference to the AudioManager responsible for
		 * processing audio commands.
		 */
		AudioSource(uint32_t sourceID, AudioManager &manager);

		/**
		 * @brief Destroys the audio source.
		 *
		 * The associated OpenAL source is released through AudioManager.
		 */
		~AudioSource();

		/**
		 * @brief Starts or resumes audio playback.
		 *
		 * Playback is performed asynchronously by the audio thread.
		 */
		void play();

		/**
		 * @brief Pauses audio playback.
		 *
		 * Playback can later be resumed by calling play().
		 */
		void pause();

		/**
		 * @brief Stops audio playback.
		 *
		 * Stopping playback resets the playback position to the beginning of
		 * the audio stream.
		 */
		void stop();

		/**
		 * @brief Assigns an audio buffer to this source.
		 *
		 * The buffer contains the decoded audio data to be played.
		 *
		 * @param buffer Shared audio buffer associated with this source.
		 */
		void setBuffer(std::shared_ptr<AudioBuffer> buffer);

		/**
		 * @brief Enables or disables looping playback.
		 *
		 * @param loop True to enable looping, false otherwise.
		 */
		void setLooping(bool loop);

		/**
		 * @brief Sets the playback pitch.
		 *
		 * Values greater than 1.0 increase playback speed and pitch, while
		 * values lower than 1.0 decrease them.
		 *
		 * @param pitch Pitch multiplier.
		 */
		void setPitch(float pitch);

		/**
		 * @brief Sets the playback gain.
		 *
		 * @param gain Volume multiplier.
		 */
		void setGain(float gain);

		/**
		 * @brief Returns the unique identifier of this audio source.
		 *
		 * @return The source identifier assigned by AudioManager.
		 */
		[[nodiscard]] uint32_t sourceID() const;

		private:
		/**
		 * @brief Audio buffer associated with this source.
		 */
		std::shared_ptr<AudioBuffer> _buffer;

		/**
		 * @brief Unique identifier assigned by AudioManager.
		 */
		uint32_t _sourceID;

		/**
		 * @brief Reference to the owning audio manager.
		 */
		AudioManager &_manager;

		/**
		 * @brief Cached playback state.
		 */
		bool _isPlaying = false;

		/**
		 * @brief Cached pitch multiplier.
		 */
		float _pitch = 1.0f;

		/**
		 * @brief Cached gain multiplier.
		 */
		float _gain = 1.0f;

		/**
		 * @brief Cached looping state.
		 */
		bool _looping = false;
	};
}	 // namespace utility::sound