#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>

class SoundBoard {
private:
	int _volume;

public:
	SoundBoard() {

	}
	~SoundBoard() {

	}

	void setVolume(int volume) { _volume = volume; }
	void togglePlay(){}

	int loadMusic(const char* filename) {
	
	}
	
	int loadSound(const char* filename) {
	
	}

	int playMusic(int music_pos) {

	}

	int playSound(int sound_pos) {

	}
};


/*	SDL STANDARD AUDIO LIBRARY SUCKS!	*/
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 4096);

	return 0;
}