#include <iostream>
#include "../hdr/SoundBoard.h"
#include "SDL.h"

SoundBoard::SoundBoard() {
	if (SDL_Init(SDL_INIT_AUDIO) == 0) {
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16SYS;
		int audio_channels = 2;
		int audio_buffers = 4096;

		// Err out on bad return value
		if (Mix_OpenAudio(audio_rate, audio_format,
			audio_channels, audio_buffers) != 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bad audio mixer init: %s", 
				Mix_GetError());
			exit(-1);
		}
	}
}

SoundBoard::~SoundBoard() {
	SDL_Quit();
}

void SoundBoard::loadSound(const char file_path[]) {
	Mix_Chunk* new_chunk = Mix_LoadWAV(file_path);

	if (new_chunk != nullptr) {
		_sound_effects.push_back(new_chunk);
		std::cout << "Sound " << _sound_effects.size() << ": " << file_path
			<< " load success...\n";
	}
	else { 
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bad sound chunk load: %s", 
			Mix_GetError());
	}
}

void SoundBoard::loadMusic(const char file_path[]) {
	Mix_Music* new_track = Mix_LoadMUS(file_path);
	if (new_track != nullptr) {
		_music_tracks.push_back(new_track);
		std::cout << "Track " << _music_tracks.size() << ": " << file_path
			<< " load success...\n";
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bad track load: %s",
			Mix_GetError());
	}
}

void SoundBoard::playSound(const int sound_pos) const {
	// Check input is legal
	if (sound_pos < _sound_effects.size()) {
		Mix_PlayChannel(-1, _sound_effects[sound_pos], 0);
		std::cout << "Playing track: " << sound_pos+1 << "\n";
	}
}

void SoundBoard::playMusic(const int track_pos) {
	if (track_pos < _music_tracks.size()) {
		Mix_PlayMusic(_music_tracks[track_pos], -1);
		_is_playing = true;
	}
}

void SoundBoard::playPause() {
	if (_is_playing && !_is_paused) { // Is playing
		Mix_PauseMusic();
		_is_paused = true;
	} else if (_is_playing&& _is_paused) { // Is Paused
		Mix_ResumeMusic();
		_is_paused = false;
	}
	else if (!_is_playing && !_is_paused) { // No track has been played yet
		playMusic(0);
	}
}