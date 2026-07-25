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
#include "utility/sound/audio_source.hpp"
#include "utility/sound/audio_manager.hpp"

utility::sound::AudioSource::AudioSource(uint32_t sourceID,
										 AudioManager &manager)
	: _sourceID(sourceID)
	, _manager(manager)
{
}

utility::sound::AudioSource::~AudioSource()
{
	_manager.destroyAudioSource(_sourceID);
}

void utility::sound::AudioSource::play()
{
	_isPlaying = true;
	_manager.submitCommand({ AudioCommandType::Play, _sourceID });
}

void utility::sound::AudioSource::pause()
{
	_isPlaying = false;
	_manager.submitCommand({ AudioCommandType::Pause, _sourceID });
}

void utility::sound::AudioSource::stop()
{
	_isPlaying = false;
	_manager.submitCommand({ AudioCommandType::Stop, _sourceID });
}

void utility::sound::AudioSource::setBuffer(std::shared_ptr<AudioBuffer> buffer)
{
	_buffer = std::move(buffer);

	AudioCommand command { AudioCommandType::SetBuffer, _sourceID, {} };
	command.data.bufferID = _buffer->bufferID();
	_manager.submitCommand(command);
}

void utility::sound::AudioSource::setLooping(bool loop)
{
	_looping = loop;
	AudioCommand command { AudioCommandType::SetLooping, _sourceID, {} };
	command.data.looping = loop;
	_manager.submitCommand(command);
}

void utility::sound::AudioSource::setPitch(float pitch)
{
	_pitch = pitch;
	AudioCommand command { AudioCommandType::SetPitch, _sourceID, {} };
	command.data.pitch = pitch;
	_manager.submitCommand(command);
}

void utility::sound::AudioSource::setGain(float gain)
{
	_gain = gain;
	AudioCommand command { AudioCommandType::SetGain, _sourceID, {} };
	command.data.gain = gain;
	_manager.submitCommand(command);
}

uint32_t utility::sound::AudioSource::sourceID() const
{
	return _sourceID;
}
