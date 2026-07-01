#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
        char name[50];
        int x;
        int y;
        int score;
        int keys;
        int health;
        char symbol; //player symbol

} Player;

char map[15][15];
int hiddenTraps[15][15];
Player players[2]; //array for 2 players

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

                if (map[randomRow][randomCol] == ' ' && hiddenTraps[randomRow][randomCol] == 0) {
                        hiddenTraps[randomRow][randomCol] = 1;
                        trapsPlaced++;
                }
        }
}

//Placing 5 random health packs
void placeHealth() {
        int healthPlaced = 0;
        while (healthPlaced < 5) {
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
        while (keysPlaced < 3) {
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
        while (doorsPlaced < 3) {
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
                        printf("%c ", map[i][j]);
                }
                printf("\n");
        }
}

void placePlayers() {
        //set stats for player 1
        players[0].health = 100;
        players[0].score = 0;
        players[0].keys = 0;
        players[0].symbol = '1';

        //set stats for player 2
        players[1].health = 100;
        players[1].score = 0;
        players[1].keys = 0;
        players[1].symbol = '2';

        //loop 2 times for players
        for (int i = 0; i < 2; i++) {
                int isPlaced = 0;  //1 = placed , 0 = not placed

                while (isPlaced == 0) {
                        int randomRow = (rand() % 13) + 1;
                        int randomCol = (rand() % 13) + 1;
                        
                        //map is empty and no hidden traps?
                        if (map[randomRow][randomCol] == ' ' && hiddenTraps[randomRow][randomCol] == 0) {
                                
                                //save x,y coordinates for each player
                                players[i].y = randomRow;
                                players[i].x = randomCol;

                                //print player symbol
                                map[randomRow][randomCol] = players[i].symbol;

                                //stops the loop and switches to the other player
                                isPlaced = 1;
                        }
                        
                }
        }
}

void movePlayer(int index) {
        char move;
        printf("Player %c, enter move (W/A/S/D): \n", players[index].symbol);
        scanf(" %c", &move);

        //Create temporary target coordinates
        int targetY = players[index].y;
        int targetX = players[index].x;

        // Adjust target based on input
        if (move == 'W' || move == 'w') {
                targetY--; 
        } else if (move == 'S' || move == 's') {
                targetY++; 
        } else if (move == 'A' || move == 'a') {
                targetX--; 
        } else if (move == 'D' || move == 'd') {
                targetX++; 
        } else {
                printf("Invalid move!\n");
                return; // Stop the function early if they typed a wrong key
        }

        // 3. Collision Detection
        if (map[targetY][targetX] == '#') {
                printf("Bonk! You hit a wall.\n");
        } else {
                // --- NEW: THE ITEM CHECKER ---
                char targetTile = map[targetY][targetX];

                // Did they step on a Treasure? 
                if (targetTile == 'T') {
                        printf("\n*** You found a treasure! +10 Points! ***\n");
                        players[index].score = players[index].score + 10;
                }

                // check if  they step on a hidden trap
                if (hiddenTraps[targetY][targetX] == 1) {
                        printf("\n*** SNAP! You stepped on a hidden trap! -20 HP! ***\n");
                        players[index].health = players[index].health - 20;
                        
                        // Disarm the trap in the hidden array so it doesn't trigger again
                        hiddenTraps[targetY][targetX] = 0;
                }
                // 4. Update the Board
        
                // Erase the player from their old spot
                map[players[index].y][players[index].x] = ' '; 

                // Update their struct with the new coordinates
                players[index].y = targetY; 
                players[index].x = targetX; 

                // Draw the player at their new spot
                map[players[index].y][players[index].x] = players[index].symbol; 
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
        placePlayers();
}

int main() {
	srand(time(NULL));
	initializeMap();

        int gameIsRunning = 1;
        int currentPlayerIndex = 0; //start with player 1

        // The Main Game Loop
        while (gameIsRunning == 1) {

                printMap();
                movePlayer(currentPlayerIndex);

                //swirch players
                if (currentPlayerIndex == 0) {
                currentPlayerIndex = 1;
                } else {
                currentPlayerIndex = 0;
                }

        // Call our new movement function
                movePlayer(currentPlayerIndex);

                // Switch players!
                // If it's 0, it becomes 1. If it's 1, it becomes 0.
                if (currentPlayerIndex == 0) {
                        currentPlayerIndex = 1;
                } else {
                        currentPlayerIndex = 0;
                }
        }

        return 0;
}
