#pragma once 
#include "luna-audio/interface/format.hpp"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
namespace luna {
namespace audio {


struct LoadedAudio {
  std::vector<std::int16_t> audio;
  std::size_t frequency = 0;
  bool loaded = false;
  Format format;
};

inline auto type_from_file(std::string file_name) -> FileType {
return FileType::WAV; // TODO make the rest work.
}

struct GlobalResources {
ALCdevice* device;
ALCcontext* context;
std::vector<std::string> devices;
std::string active;

GlobalResources();
~GlobalResources();
auto load_WAV(std::string_view a) -> LoadedAudio;
auto check_al_errors() -> void;
};

auto global_resources() -> GlobalResources&;
}
}