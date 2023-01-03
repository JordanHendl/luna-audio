#pragma once
#include <string>
#include <vector>
namespace luna {
namespace audio {
struct Device {
  std::string name;
};

auto get_audio_devices() -> std::vector<Device>;
auto set_current_device(std::string name) -> void;
auto get_current_device() -> std::string;
}
}