#include "sound/test_wav_decoder.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "utility/sound/decoder/wav_decoder.hpp"

using namespace utility::sound;
using namespace tests::utility::sound;

namespace
{
	// A canonical PCM WAV file: RIFF header, 16-byte fmt chunk, data chunk.
	std::vector<std::byte> makePcmWav(uint16_t channels, uint16_t bits,
									  uint32_t frames)
	{
		const uint16_t blockAlign = static_cast<uint16_t>(channels * bits / 8);
		const uint32_t dataSize	  = frames * blockAlign;
		std::vector<std::byte> out;
		auto put = [&out](uint32_t value, int bytes) {
			for (int i = 0; i < bytes; ++i) {
				out.push_back(static_cast<std::byte>(value >> (8 * i)));
			}
		};
		auto tag = [&out](const char *text) {
			for (int i = 0; i < 4; ++i) {
				out.push_back(static_cast<std::byte>(text[i]));
			}
		};
		tag("RIFF");
		put(36 + dataSize, 4);
		tag("WAVE");
		tag("fmt ");
		put(16, 4);
		put(1, 2);	  // WAVE_FORMAT_PCM
		put(channels, 2);
		put(8000, 4);
		put(8000 * blockAlign, 4);
		put(blockAlign, 2);
		put(bits, 2);
		tag("data");
		put(dataSize, 4);
		for (uint32_t i = 0; i < dataSize; ++i) {
			out.push_back(static_cast<std::byte>(i));
		}
		return out;
	}
}	 // namespace

// Before the fix, every width above 8 bits wrote past the decoder's sample
// buffer; the sanitizers workflow reports it as a heap-buffer-overflow.
TEST_F(TestWavDecoder, DecodesEveryPcmSampleWidth)
{
	for (uint16_t channels: { 1, 2 }) {
		for (uint16_t bits: { 8, 16, 24, 32 }) {
			auto file = std::make_shared<utility::File>(
				"test.wav", makePcmWav(channels, bits, 64));
			WAVDecoder decoder;
			EXPECT_NE(decoder.decode(file), nullptr)
				<< channels << " channel(s), " << bits << " bits";
		}
	}
}
