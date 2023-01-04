#include <gtest/gtest.h>
#include "luna-audio/audio.hpp"
#include "unit_tests/raw_files/test_audio.hpp"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;
namespace luna::audio::interface_test {
  TEST(Interface, CreateSound) {
    constexpr auto cSize = sizeof(__test_raw) / sizeof(std::int16_t);
    constexpr auto cFormat = Format::Stereo16;
    constexpr auto cFrequency = 44.1_kHz;
    auto vec = std::vector<std::int16_t>(cSize);
    auto raw_ptr = reinterpret_cast<const std::int16_t *>(&__test_raw[0]);
    std::copy(raw_ptr, raw_ptr + cSize, vec.begin());
    auto sound = Sound(vec, cFrequency, cFormat);
    sound.play({});
    std::this_thread::sleep_for(500ms); // Make sure multiple sounds can be played asynchronously
    sound.play({}).wait();
  }
}