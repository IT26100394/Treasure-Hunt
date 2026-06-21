#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char map[15][15];
int hiddenTraps[15][15];

//placing 30 random interior walls
void placeWalls() {
	int wallsPlaced = 0;
	while (wallsPlaced < 30) {
		int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = '#';
                        wallsPlaced++;
                }
        }
}

//placing 12 random Treasures
void placeTreasures() {
	int treasuresPlaced = 0;
	while (treasuresPlaced < 12) {
		int randomRow = (rand() % 13) + 1;
		int randomCol = (rand() % 13) + 1;
		
		if (map[randomRow][randomCol] == ' ') {
			map[randomRow][randomCol] = 'T';
		        treasuresPlaced++;
		}
	}		
}

//placing 10 random Traps
void placeTraps() {
	int trapsPlaced = 0;
	while (trapsPlaced < 10) {
		int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = '@';
                        trapsPlaced++;
                }
        }
}

//Placing 5 random health packs
void placeHealth() {
        int healthPlaced = 0;
        while (healthPlaced < 10) {
                int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = 'H';
                        healthPlaced++;
                }
        }
}

//Placing 3 random Keys
void placeKeys() {
        int keysPlaced = 0;
        while (keysPlaced < 10) {
                int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = 'K';
                        keysPlaced++;
                }
        }
}

//Placing 3 random doors
void placeDoors() {
        int doorsPlaced = 0;
        while (doorsPlaced < 10) {
                int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = 'D';
                        doorsPlaced++;
                }
        }
}


//print the full map
void printMap() {
	for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                        printf("%c", map[i][j]);
                }
                printf("\n");
        }
}

// Setup exterior walls, interior empty spaces and Traps
void initializeMap() {
        for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {

                        if (i == 0 || i == 14 || j == 0 || j  == 14){
                                map[i][j] = '#';
                        }
                        else {
                                map[i][j] = ' ';
                        }

                        hiddenTraps[i][j] = 0;
                }
        }
	placeWalls();
	placeTreasures();
	placeDoors();
	placeHealth();
	placeTraps();
	placeKeys();
}

int main() {
	srand(time(NULL));
	initializeMap();
	printMap();

	return 0;
}
