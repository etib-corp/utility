#include <chrono>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <utility/sound/audio_manager.hpp>
#include <utility/sound/decoder/decoder_registry.hpp>
#include <utility/system_io/file.hpp>

namespace
{
	std::shared_ptr<utility::File> readFile(const std::string &path)
	{
		std::ifstream input(path, std::ios::binary | std::ios::ate);
		if (!input) {
			return nullptr;
		}

		const auto size = input.tellg();
		if (size < 0) {
			return nullptr;
		}

		std::vector<std::byte> content(static_cast<std::size_t>(size));
		input.seekg(0, std::ios::beg);
		if (!content.empty()
			&& !input.read(reinterpret_cast<char *>(content.data()), size)) {
			return nullptr;
		}

		return std::make_shared<utility::File>(path, content);
	}
}	 // namespace

int main(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: utility_sound_mp3 <audio.mp3> [seconds]\n";
		return 1;
	}

	int seconds = 5;
	if (argc == 3) {
		try {
			seconds = std::stoi(argv[2]);
		} catch (const std::exception &) {
			std::cerr << "Duration must be a positive integer.\n";
			return 1;
		}
	}
	if (seconds <= 0) {
		std::cerr << "Duration must be a positive integer.\n";
		return 1;
	}

	utility::sound::AudioManager audioManager;
	if (!audioManager.isRunning()) {
		std::cerr << "No OpenAL playback device is available.\n";
		return 1;
	}

	auto file = readFile(argv[1]);
	if (!file) {
		std::cerr << "Could not read MP3 file: " << argv[1] << "\n";
		return 1;
	}

	auto decoder = utility::sound::DecoderRegistry::getDecoderForFile(
		file->path(), utility::sound::AudioDecoderType::MP3);
	if (!decoder) {
		std::cerr << "No MP3 decoder is available.\n";
		return 1;
	}

	try {
		auto buffer = decoder->decode(file);
		if (!buffer) {
			std::cerr << "Could not decode MP3 file: " << argv[1] << "\n";
			return 1;
		}

		auto source = audioManager.createAudioSource(buffer);
		source->setGain(1.0f);
		source->play();

		std::cout << "Playing " << argv[1] << " for " << seconds
				  << " seconds.\n";
		std::this_thread::sleep_for(std::chrono::seconds(seconds));
		source->stop();
	} catch (const std::exception &error) {
		std::cerr << "Audio playback failed: " << error.what() << '\n';
		return 1;
	}

	return 0;
}