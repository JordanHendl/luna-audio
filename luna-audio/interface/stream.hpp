#pragma once
#include "luna-audio/interface/format.hpp"
#include <cstddef>
#include <memory>
#include <vector>
#include <string_view>
namespace luna {
namespace audio {
struct StreamPlayInfo {
  float xpos = 0.0f;
  float ypos = 0.0f;
  float zpos = 0.0f;
  float pitch = 1.0f;
  float gain = 1.0f;
  std::size_t num_loops = 1;
};

class Stream {
public:
  Stream(const Stream& cpy) = delete;
  auto operator=(const Stream& cpy) -> Stream& = delete;
  
  Stream();
  Stream(std::string_view file_path);
  Stream(const unsigned char* raw_pcm, std::size_t size, std::size_t frequency, Format format);
  Stream(std::vector<unsigned char> raw_pcm, std::size_t frequency, Format format);
  Stream(Stream&& mv) = default;
  ~Stream();
  auto play(StreamPlayInfo info) -> void;
  auto stop() -> void;
private:
  struct StreamData;
  std::unique_ptr<StreamData> m_data;
};
}
}