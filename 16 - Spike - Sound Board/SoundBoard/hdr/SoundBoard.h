#include <vector>
#include "SDL_mixer.h"
#pragma once

class SoundBoard {
public:
	SoundBoard();
	~SoundBoard();

	void loadSound(const char file_path[]);
	void loadMusic(const char file_path[]);
	void playSound(const int sound_pos) const;
	void playMusic(const int track_pos);
	void playPause();

private:
	// These pertain to music not sounds
	bool _is_playing = false;
	bool _is_paused = false;

	std::vector<Mix_Chunk*> _sound_effects;
	std::vector<Mix_Music*> _music_tracks;
}; 