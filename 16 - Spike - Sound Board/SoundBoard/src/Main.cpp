#include <iostream>
#include <SDL.h>

/*	Have a discussion with clinton regarding the best way to approach pausing 
*	the soundboard. It's possible to run the audio stream on a seperate thread,
*	maybe use sdl mixer? My issue is the delay function required to actually 
*	hear the bloody sound. 
*
*	Just depends if SDL Mixer is on the table for the spike...	
*/

class SoundBoard {
public:
	void playSound(const char* file_name, Uint32 ms_delay) {
		SDL_AudioSpec wav_spec;
		Uint8* wav_buffer;
		Uint32 wav_length;

		SDL_LoadWAV(file_name, &wav_spec, &wav_buffer, &wav_length);
		SDL_AudioDeviceID audio_device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

		int is_success = SDL_QueueAudio(audio_device_id, wav_buffer, wav_length);
		SDL_PauseAudioDevice(audio_device_id, 0); // Play da stuf
		SDL_Delay(ms_delay);

		SDL_CloseAudioDevice(audio_device_id);
		SDL_FreeWAV(wav_buffer);
	}
};


int main(int argc, char* argv[]) {
	//Init SDL subsystems, window and renderer.
	SDL_Init(SDL_INIT_EVERYTHING);
	
	bool is_running = true;
	SDL_Window* window = SDL_CreateWindow("Task 12 - SDL2 Concepts, Thomas Horsley 103071494",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SoundBoard sound_board;

	//	Set window color to green initially
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (is_running) {
		SDL_Event event;
		const Uint8* keystates = SDL_GetKeyboardState(NULL);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { is_running = false; }
			if (keystates[SDL_SCANCODE_Q]) { is_running = false; }

			if (keystates[SDL_SCANCODE_0]){
				
			}

			if (keystates[SDL_SCANCODE_1]){
				sound_board.playSound("audio/Funny_1.wav", 10000);
			}

			if (keystates[SDL_SCANCODE_2]){
				sound_board.playSound("audio/Funny_2.wav", 20000);
			}

			if (keystates[SDL_SCANCODE_3]) {
				sound_board.playSound("audio/Rats_Birthday_Mixtape.wav", 25000);
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}