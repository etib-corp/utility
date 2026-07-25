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
#include "utility/sound/audio_buffer.hpp"

utility::sound::AudioBuffer::AudioBuffer()
{
}

utility::sound::AudioBuffer::~AudioBuffer()
{
	alDeleteBuffers(1, &_bufferID);
}

ALuint utility::sound::AudioBuffer::bufferID() const
{
	return _bufferID;
}

void utility::sound::AudioBuffer::upload(const DecodedAudio &decodedAudio)
{
	if (_bufferID != 0) {
		alDeleteBuffers(1, &_bufferID);
	}

	alGenBuffers(1, &_bufferID);
	alBufferData(_bufferID, decodedAudio.format, decodedAudio.samples.data(),
				 static_cast<ALsizei>(decodedAudio.samples.size()),
				 decodedAudio.sampleRate);
}