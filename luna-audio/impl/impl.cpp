#include "luna-audio/impl/impl.hpp"
#define DR_WAV_IMPLEMENTATION
#define DR_MP3_IMPLEMENTATION
#define DR_FLAC_IMPLEMENTATION
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include "external/dr_flac.h"
#include "external/dr_mp3.h"
#include "external/dr_wav.h"

namespace luna {
namespace audio {
auto enumerate_devices() -> std::vector<std::string> {
  auto can_enumerate = false;
  auto out = std::vector<std::string>();

  can_enumerate = alcIsExtensionPresent(nullptr, "ALC_ENUMERATION_EXT");

  if(can_enumerate) {
    auto devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
    auto len = 0;
    auto device = devices;
    auto next = devices + 1;

    while(device && *device != '\0' && next && *next != '\0') {
      out.push_back(std::string(device));
      len = std::strlen(device);
      device += (len+1);
      next +=(len+2);
    }
  }
  return out;
}

GlobalResources::GlobalResources() {
  this->context = nullptr;
  this->device = nullptr;
  this->context = alcCreateContext( this->device, nullptr ) ;
  assert(this->context);
  assert(alcMakeContextCurrent(this->context));

  this->devices = enumerate_devices();

  // Open default system audio device.
  this->device = alcOpenDevice(nullptr);
  assert(this->device);
}

auto GlobalResources::load_WAV(std::string_view file) -> LoadedAudio {
    auto out = LoadedAudio();
    auto channels = 0u;
    auto sample_rate = 0u;
    auto count = drwav_uint64();
    auto stereo = false;
    auto wav = drwav();

    if(!drwav_init_file( &wav, file.data(), nullptr)) {
      return {};
    }
    
    auto tmp = drwav__read_pcm_frames_and_close_s16( &wav, &channels, &sample_rate, &count ) ;
    auto size = wav.totalPCMFrameCount * channels * sizeof(int16_t);
    out.frequency = wav.sampleRate;
    stereo = channels > 1;
    out.format = stereo ? Format::Stereo16 : Format::Mono16;
    
    out.audio.resize(size);
    std::copy(tmp, tmp+size, out.audio.begin());
    if(out.audio.empty()) out.loaded = true;
    return out;
}

auto global_resources() -> GlobalResources& {
  static GlobalResources g;
  return g;
}

auto check_al_errors() -> void {
    auto error_str = std::string();
    auto error = alGetError();
    if( error != AL_NO_ERROR ) {
      switch( error ) {
        case AL_INVALID_NAME : error_str = "Invalid name paramater passed to AL call."; break;
        case AL_INVALID_ENUM : error_str = "Invalid enum paramater passed to AL call."; break;
        case AL_INVALID_VALUE : error_str = "Invalid value paramater passed to AL call."; break;
        case AL_INVALID_OPERATION : error_str = "Illegal AL call."; break;
        case AL_OUT_OF_MEMORY : error_str = "Out of memory."; break;
        default                   : break ;
      }
      std::cout << "OpenAl Error! " << error_str << std::endl;
      assert(error != AL_NO_ERROR);
    }
}
}
}