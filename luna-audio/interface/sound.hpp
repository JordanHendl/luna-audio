#pragma once
#include "luna-audio/interface/format.hpp"
#include <memory>
#include <vector>
#include <cstddef>
#include <string_view>
#include <future>
namespace luna {
namespace audio {
struct SoundPlayInfo {
  float xpos = 0.0f;
  float ypos = 0.0f;
  float zpos = 0.0f;
  float pitch = 1.0f;
  float gain = 1.0f;
  std::size_t num_loops = 1;
};

class Sound {
public:
  Sound(const Sound& cpy) = delete;
  auto operator=(const Sound& cpy) -> Sound& = delete;

  Sound();
  Sound(std::string_view file_path);
  Sound(const std::int16_t* raw_pcm, std::size_t size, std::size_t frequency, Format format);
  Sound(const std::int32_t* raw_pcm, std::size_t size, std::size_t frequency, Format format);
  Sound(const std::vector<std::int16_t>& raw_pcm, std::size_t frequency, Format format);
  Sound(const std::vector<std::int32_t>& raw_pcm, std::size_t frequency, Format format);
  Sound(Sound&& mv) = default;
  ~Sound();
  auto play(SoundPlayInfo info) -> std::future<void>;
  auto stop() -> void;
private:
  struct SoundData;
  std::unique_ptr<SoundData> m_data;
};
}
}