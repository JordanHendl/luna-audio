#pragma once
namespace luna {
namespace audio {
enum class FileType {
  WAV,
  FLAC,
  MP3
};

enum class Format {
  Stereo32,
  Mono32,
  Stereo24,
  Mono24,
  Stereo16,
  Mono16,
  Stereo8,
  Mono8,
};
}
}