#include<iostream>
#include<cctype>

using namespace std;

class World {
private:
	int mapSize = 64;
	char map[64] = { '#', '#', '#', '#', '#', '#', '#', '#',
					 '#', '#', ' ', '^', '#', ' ', ' ', '#',
					 '#', ' ', ' ', ' ', '#', ' ', ' ', '#',
					 '#', '^', ' ', '#', '#', ' ', ' ', '#',
					 '#', ' ', ' ', ' ', ' ', ' ', '^', '#',
					 '#', ' ', ' ', '#', 'G', ' ', '#', '#',
					 '#', 'S', ' ', '#', ' ', '^', '#', '#',
					 '#', '#', '#', '#', '#', '#', '#', '#',};
	
	int playerPosition = 49; //Value corresponding element S
	bool gameRunning = true;

	char* findValidMoves() {	
		//* Dynamic arrays are pretty cewl, I'm assuming it's auto-deleted when
		//* out of scope.
		char* validMoves = new char[4];
		
		//'T' is a default value loaded for later presentation functionss
		for(int i = 0; i < 4; i++){
			validMoves[i] = 'T';
		}

		if(map[playerPosition - 8] != '#'){
			validMoves[0] = 'N';
		}
		if(map[playerPosition + 1] != '#'){
			validMoves[1] = 'E';
		}
		if(map[playerPosition + 8] != '#'){
			validMoves[2] = 'S';
		}
		if(map[playerPosition - 1] != '#'){
			validMoves[3] = 'W';
		}
		return validMoves;
	}

	void handleEvents(){
		if(map[playerPosition] == '^'){
			cout << "AH! Man's hit a spike!" << endl;
			gameRunning = false;
		}
		if(map[playerPosition] == 'G'){
			cout << "Good job, you got the goop!" << endl;
			gameRunning = false;
		}
	}
	
	//Only presents movement directions, ommits default array values
	void presentValidMoves(){
		char* validMoves = findValidMoves();

		cout << "You can move: ";

		for(int i = 0; i < 4; i++){
			if (validMoves[i] != 'T'){
				cout << validMoves[i] << ", ";
			}
		}
		cout << endl;
	}

	void handleInput(char input){
		switch (input){
			case 'N':
				playerPosition -= 8;
				break;	
			case 'E':
				playerPosition += 1;
				break;
			case 'S':
				playerPosition += 8;
				break;
			case 'W':
				playerPosition -= 1;
				break;
			case 'Q':
				playerPosition += 0;
				gameRunning = false;
			default:
				playerPosition += 0;
				break;
		}
	}

	void printMap(){	
		for(int count = 0; count < 64; count++){
				if(count % 8 == 7){
					cout << map[count] << endl;
				}
				else{
					cout << map[count];
				}
			}
	}	

public:
	World(){
		render();
	}

	bool getGameRunning(){
		return gameRunning;
	}

	char getInput(){
		char input;
		cin >> input;
		char upper_case_char = toupper(input);

		return upper_case_char;
	}	
	
	void update() {
		presentValidMoves();
		
		char input = getInput();
		handleInput(input);
		handleEvents();
	}

	/*Though personally I don't see the need for a render function within
	  a CLI game it was specified in the deliverables. This function will
	  simply reprint the starting map each turn.*/
	void render(){
		printMap();
	}

};

void introSec() {
	cout << "Welcome to Gridworld: Quantised Excitement!" << endl;
	cout << "Fate is waiting for you! (Coder: Thomas Horsley - 103071494)" << endl;
	cout << "Valid commands: N, E, S & W for Direction. Q to quit" << endl;
	cout << endl;
}

int main() {
	introSec();
	World world;

	while(world.getGameRunning() == true){
		world.update();
		world.render();
	}
	return 0;
}

