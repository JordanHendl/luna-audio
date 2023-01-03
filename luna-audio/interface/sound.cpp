#include "luna-audio/interface/sound.hpp"
#include "luna-audio/impl/impl.hpp"
namespace luna {
namespace audio {
struct Sound::SoundData {
};
Sound::Sound() {

}

Sound::Sound(std::string_view file_path) {

}

Sound::Sound(const unsigned char* raw_pcm, std::size_t size, std::size_t frequency, Format format) {

}

Sound::Sound(std::vector<unsigned char> raw_pcm, std::size_t frequency, Format format) {

}

Sound::~Sound() {
}

auto Sound::play(SoundPlayInfo info) -> void {

}

auto Sound::stop() -> void {

}
}
}