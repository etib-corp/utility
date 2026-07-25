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
#include "utility/sound/audio_manager.hpp"

utility::sound::AudioManager::AudioManager()
{
	_device = alcOpenDevice(nullptr);
	if (!_device) {
		getLogger().error() << "Failed to open audio device";
		throw std::runtime_error("Failed to open audio device");
	}

	_context = alcCreateContext(_device, nullptr);
	if (!_context) {
		getLogger().error() << "Failed to create audio context";
		alcCloseDevice(_device);
		throw std::runtime_error("Failed to create audio context");
	}

	getLogger().info() << "Audio manager initialized successfully";

	_audioThread = std::thread(&AudioManager::threadLoop, this);
}

utility::sound::AudioManager::~AudioManager()
{
	stop();

	if (_audioThread.joinable())
		_audioThread.join();

	alcDestroyContext(_context);
	alcCloseDevice(_device);

	getLogger().info() << "Audio manager shut down";
}

void utility::sound::AudioManager::submitCommand(const AudioCommand &command)
{
	std::lock_guard<std::mutex> lock(_commandQueueMutex);
	_commandQueue.push_back(command);
}

std::unique_ptr<utility::sound::AudioSource>
	utility::sound::AudioManager::createAudioSource(
		std::shared_ptr<AudioBuffer> buffer)
{
	auto id = _nextSourceID++;

	auto audioSource = std::make_unique<AudioSource>(id, *this);

	submitCommand({ AudioCommandType::CreateSource, id, {} });

	{
		std::lock_guard<std::mutex> lock(_sourcesMutex);
		_sources[id] = 0;	 // Placeholder for ALuint source ID
	}

	getLogger().debug() << "Created audio source with ID: " << id;

	audioSource->setBuffer(buffer);

	return audioSource;
}

void utility::sound::AudioManager::destroyAudioSource(uint32_t sourceID)
{
	std::lock_guard lock(_sourcesMutex);

	auto it = _sources.find(sourceID);

	if (it == _sources.end())
		return;

	ALuint alId = it->second;

	alSourceStop(alId);
	alSourcei(alId, AL_BUFFER, 0);
	alDeleteSources(1, &alId);

	_sources.erase(it);
}

void utility::sound::AudioManager::stop()
{
	getLogger().info() << "Stopping audio manager";
	_running = false;
}

bool utility::sound::AudioManager::isRunning() const
{
	return _running;
}

void utility::sound::AudioManager::threadLoop()
{
	alcMakeContextCurrent(_context);

	while (_running) {
		processCommands();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	processCommands();	  // Process any remaining commands before shutting down

	alcMakeContextCurrent(nullptr);
}

void utility::sound::AudioManager::processCommands()
{
	std::deque<AudioCommand> commandsToProcess;

	{
		std::lock_guard<std::mutex> lock(_commandQueueMutex);
		commandsToProcess.swap(_commandQueue);
	}

	while (!commandsToProcess.empty()) {
		executeCommand(commandsToProcess.front());
		commandsToProcess.pop_front();
	}
}

void utility::sound::AudioManager::executeCommand(const AudioCommand &command)
{
	ALuint alId;
	{
		std::lock_guard<std::mutex> lock(_sourcesMutex);
		auto it = _sources.find(command.sourceID);
		if (it == _sources.end()) {
			getLogger().warning()
				<< "Audio command failed: source not found (ID: "
				<< command.sourceID << ")";
			return;
		}
		alId = it->second;
	}

	switch (command.type) {
		case AudioCommandType::Play:
			alSourcePlay(alId);
			break;
		case AudioCommandType::Stop:
			alSourceStop(alId);
			break;
		case AudioCommandType::Pause:
			alSourcePause(alId);
			break;
		case AudioCommandType::SetPosition:
			// source->setPosition(command.data.position);
			break;
		case AudioCommandType::SetGain:
			alSourcef(alId, AL_GAIN, command.data.gain);
			break;
		case AudioCommandType::SetPitch:
			alSourcef(alId, AL_PITCH, command.data.pitch);
			break;
		case AudioCommandType::SetLooping:
			alSourcei(alId, AL_LOOPING,
					  command.data.looping ? AL_TRUE : AL_FALSE);
			break;
		case AudioCommandType::CreateSource: {
			ALuint newSource;
			alGenSources(1, &newSource);
			{
				std::lock_guard<std::mutex> lock(_sourcesMutex);
				_sources[command.sourceID] = newSource;
			}
		} break;
		case AudioCommandType::SetBuffer:
			alSourcei(alId, AL_BUFFER, command.data.bufferID);
			break;
		case AudioCommandType::DestroySource:
			alSourceStop(alId);
			alDeleteSources(1, &alId);
			{
				std::lock_guard<std::mutex> lock(_sourcesMutex);
				_sources.erase(command.sourceID);
			}
			break;
		default:
			getLogger().warning() << "Unknown audio command type";
			break;
	}
}
