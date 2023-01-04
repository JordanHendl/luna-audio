#include "luna-audio/interface/sound.hpp"
#include "luna-audio/impl/impl.hpp"
#include <variant>
#include <thread>
#include <chrono>
#include <iostream>
#include <numeric>
using namespace std::chrono_literals;
namespace luna {
namespace audio {
struct Sound::SoundData {
  unsigned al_buffer = 0;
  using RawSound = std::variant<LoadedAudio<std::int16_t>, LoadedAudio<std::int32_t>>;
  RawSound data;

  Sound::SoundData() {
    alGenBuffers(1, &this->al_buffer);
    check_al_errors();
  }
};

Sound::Sound() {
  this->m_data = std::make_unique<Sound::SoundData>();  
}

Sound::Sound(std::string_view file_path) {
  auto& res = global_resources();
  this->m_data = std::make_unique<Sound::SoundData>();
  this->m_data->data = res.load_WAV<std::int16_t>(file_path);
}

Sound::Sound(const std::int16_t* raw_pcm, std::size_t size, std::size_t frequency, Format format) {
  auto& res = global_resources();
  this->m_data = std::make_unique<Sound::SoundData>();
  auto tmp = LoadedAudio<std::int16_t>{{}, frequency, true, format};
  tmp.audio.assign(raw_pcm, raw_pcm + size);
  this->m_data->data = std::move(tmp);
  alBufferData(m_data->al_buffer, convert(format), reinterpret_cast<const ALvoid*>(raw_pcm), size, frequency);
}

Sound::Sound(const std::int32_t* raw_pcm, std::size_t size, std::size_t frequency, Format format) {
  auto& res = global_resources();
  this->m_data = std::make_unique<Sound::SoundData>();
  auto tmp = LoadedAudio<std::int32_t>{{}, frequency, true, format};
  tmp.audio.assign(raw_pcm, raw_pcm + size);
  this->m_data->data = std::move(tmp);
  alBufferData(m_data->al_buffer, convert(format), reinterpret_cast<const ALvoid*>(raw_pcm), size, frequency);
}

Sound::Sound(const std::vector<std::int16_t>& raw_pcm, std::size_t frequency, Format format) {
  auto& res = global_resources();
  this->m_data = std::make_unique<Sound::SoundData>();
  this->m_data->data = LoadedAudio<std::int16_t>{raw_pcm, frequency, true, format};
  alBufferData(m_data->al_buffer, convert(format), reinterpret_cast<const ALvoid*>(raw_pcm.data()), raw_pcm.size(), frequency);
}

Sound::Sound(const std::vector<std::int32_t>& raw_pcm, std::size_t frequency, Format format) {
  auto& res = global_resources();
  this->m_data = std::make_unique<Sound::SoundData>();
  this->m_data->data = LoadedAudio<std::int32_t>{raw_pcm, frequency, true, format};
  alBufferData(m_data->al_buffer, convert(format), reinterpret_cast<const ALvoid*>(raw_pcm.data()), raw_pcm.size(), frequency);
}

Sound::~Sound() {
}

auto Sound::play(SoundPlayInfo info) -> std::future<void> {
  auto& res = global_resources();
  auto source = std::numeric_limits<unsigned int>::max();
  res.cleanup_sources();
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, this->m_data->al_buffer);
  alSourcef(source, AL_PITCH, info.pitch);
  alSourcef(source, AL_GAIN , info.gain);
  alSource3f(source, AL_POSITION, info.xpos, info.ypos, info.zpos);
  alSource3f(source, AL_VELOCITY, 0.f, 0.f, 0.f);
  alSourcef(source, AL_LOOPING , false);
  alSourcePlay(source);
  return std::async(std::launch::deferred, [](unsigned source) {
    int state = std::numeric_limits<int>::max();
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    while(state == AL_PLAYING || state == AL_INITIAL) {
      alGetSourcei(source, AL_SOURCE_STATE, &state);
      check_al_errors();
    }
  }, source);
}

auto Sound::stop() -> void {
  auto& res = global_resources();
  res.cleanup_sources();
  // TODO 
}
}
}