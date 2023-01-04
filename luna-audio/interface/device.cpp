#include "luna-audio/interface/device.hpp"
#include "luna-audio/impl/impl.hpp"
namespace luna {
namespace audio {
auto get_audio_devices() -> std::vector<Device> {
  auto& res = global_resources();
  auto out = std::vector<Device>();
  for(auto& a : res.devices) {
    out.push_back({a.first});
  }

  return out;
}

auto set_current_device(std::string name) -> void {

}

auto get_current_device() -> std::string {
  return global_resources().active;
}
}
}