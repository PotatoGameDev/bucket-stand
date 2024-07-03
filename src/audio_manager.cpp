#include "audio_manager.h"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <utility>

namespace potato_bucket {
AudioMan::~AudioMan(){};

float CalculateVolume(Vector2 listener, Vector2 source) {
  float distance = Vector2Distance(listener, source);
  float maxDistance = 500.0f;
  return Clamp(1.0f - (distance / maxDistance), 0.0f, maxDistance);
}

float CalculatePan(Vector2 listener, Vector2 source) {
  float pan =
      Remap(source.x - listener.x, static_cast<float>(-GetScreenWidth()) / 2,
            static_cast<float>(GetScreenWidth()) / 2, 0.0f, 1.0f);
  pan = Clamp(pan, 0.0f, 1.0f);
  return pan;
}

void AudioMan::play(std::string fileName, Vector2 playerPos,
                    Vector2 soundSourcePos) {
  float volume = CalculateVolume(playerPos, soundSourcePos);
  float pan = CalculatePan(playerPos, soundSourcePos);

  auto found = cache.find(fileName);
  if (found != cache.end()) {
    if (volume <= 0.0) {
      return;
    }
    Sound sound = found->second;
    SetSoundVolume(sound, volume);
    SetSoundPan(sound, pan);
    PlaySound(sound);
  }

  Sound sound = LoadSound(("resources/" + fileName).c_str());
  auto inserted = cache.insert(std::make_pair(fileName, std::move(sound)));

  if (volume <= 0.0) {
    return;
  }

  SetSoundVolume(inserted.first->second, volume);
  SetSoundPan(inserted.first->second, pan);
  PlaySound(inserted.first->second);
}

void AudioMan::unload() {
  for (auto pair : cache) {
    UnloadSound(pair.second);
  }
}
} // namespace potato_bucket
