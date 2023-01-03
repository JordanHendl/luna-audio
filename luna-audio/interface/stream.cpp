#include "luna-audio/interface/Stream.hpp"
#include "luna-audio/impl/impl.hpp"
namespace luna {
namespace audio {
struct Stream::StreamData {
};
Stream::Stream() {

}

Stream::Stream(std::string_view file_path) {

}

Stream::Stream(const unsigned char* raw_pcm, std::size_t size, std::size_t frequency, Format format) {

}

Stream::Stream(std::vector<unsigned char> raw_pcm, std::size_t frequency, Format format) {

}

Stream::~Stream() {
}

auto Stream::play(StreamPlayInfo info) -> void {

}

auto Stream::stop() -> void {

}
}
}