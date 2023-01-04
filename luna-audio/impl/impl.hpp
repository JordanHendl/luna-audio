#pragma once 
#include "luna-audio/interface/format.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>

namespace luna {
namespace audio {
inline auto convert(Format format) -> int {
  switch( format )
  {
    case Format::Stereo32 : return AL_FORMAT_STEREO_FLOAT32 ;
    case Format::Mono32   : return AL_FORMAT_MONO_FLOAT32   ;
    case Format::Stereo16 : return AL_FORMAT_STEREO16       ;
    case Format::Mono16   : return AL_FORMAT_MONO16         ;
    case Format::Stereo8  : return AL_FORMAT_STEREO8        ;
    case Format::Mono8    : return AL_FORMAT_MONO8          ;
    default               : return AL_FORMAT_STEREO16       ;
  };
}

template<typename Type>
struct LoadedAudio {
  std::vector<Type> audio;
  std::size_t frequency = 0;
  bool loaded = false;
  Format format;
};

inline auto type_from_file(std::string file_name) -> FileType {
return FileType::WAV; // TODO make the rest work.
}

struct DeviceInfo {
  ALCdevice* device;
  ALCcontext* context;
};

auto check_al_errors() -> void;
struct GlobalResources {

std::list<unsigned> sources;
std::unordered_map<std::string, DeviceInfo> devices;
std::string active;

GlobalResources();
~GlobalResources();

template<typename Type>
auto load_WAV(std::string_view a) -> LoadedAudio<Type>;
auto make_device_current(std::string_view name) -> void;

auto cleanup_sources() -> void {
  auto iter = this->sources.begin();
  while(iter != this->sources.end()) {
    auto source = *iter;
    int state = std::numeric_limits<int>::max();
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if(state == AL_STOPPED) {
      alDeleteSources(1, &source);
      this->sources.erase(iter++);
    } else {
      ++iter;
    }
  }
}
};

auto global_resources() -> GlobalResources&;
}
}