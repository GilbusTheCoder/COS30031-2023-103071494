#include <iostream>
#include "../hdr/SoundBoard.h"

int main(int argc, char* argv[]) {
	SoundBoard sound_board;

	sound_board.loadSound("audio/BombHasBeenPlanted.wav");
	sound_board.loadSound("audio/RecordScratchSoundEffect.wav");
	sound_board.loadSound("audio/ThrowingFlashbangSoundEffectCSGO.wav");
	sound_board.loadMusic("audio/RatsBirthdayMixtape.mp3");

	sound_board.playMusic(0);

	int choice = 0;
	while (choice != -1) {
		choice = 0;
		std::cout << "\nEnter a sound to play using num input\n";
		std::cout << "-1 to exit...\n";
		std::cout << ">> ";
		std::cin >> choice;

		if (choice == 9) {
			sound_board.playPause();
		}

		sound_board.playSound(choice - 1);
		std::cin.clear();
	}

	return 0;
}
