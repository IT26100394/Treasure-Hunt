#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
        char name[50];
        int x;
        int y;
        int score;
        int keys;
        int health;
        char symbol; //player symbol

        //for part B
        int movesMade;
        int treasuresFound;
        int trapsTriggered;
        int damageTaken;
        int healthPacksUsed;
        int keysCollected;
        int doorsUnlocked;

} Player;

char map[15][15];
int hiddenTraps[15][15];
Player players[3]; //array for 3 players

int totalActivePlayers = 0;
int currentRound = 1;
void saveGame();
void loadGame();
int checkWin();
int checkLoss();

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
        for(int i = 0; i < totalActivePlayers; i++) {

                //set stats for players
                players[i].health = 100;
                players[i].score = 0;
                players[i].keys = 0;

                //assign player number
                players[i].symbol = '1' + i;

                //set stats for players
                players[i].movesMade = 0;
                players[i].treasuresFound = 0;
                players[i].trapsTriggered = 0;
                players[i].damageTaken = 0;
                players[i].healthPacksUsed = 0;
                players[i].keysCollected = 0;
                players[i].doorsUnlocked = 0;

                //place the players in the map
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
        char moves[5]; //can hold 4 moves and 1 \0 character

        printf("Player %c, enter 4 moves (W/A/S/D) or Q to save: ", players[index].symbol);
        scanf("%4s", moves);

        //save game option
        if (moves[0] == 'Q' || moves[0] == 'q') {
                saveGame();
        }

        for (int i = 0; i < 4; i++) {
                if (moves[i] == '\0') {
                        break; 
                }

                char currentMove = moves[i];
                int Ycoordi = players[index].y;
                int Xcoordi = players[index].x;

                if (currentMove == 'W' || currentMove == 'w') {
                        Ycoordi--; 
                } else if (currentMove == 'S' || currentMove == 's') {
                        Ycoordi++; 
                } else if (currentMove == 'A' || currentMove == 'a') {
                        Xcoordi--; 
                } else if (currentMove == 'D' || currentMove == 'd') {
                        Xcoordi++; 
                } else {
                        printf("Invalid move. Character skipped: %c\n", currentMove);
                        continue; 
                }

                if (map[Ycoordi][Xcoordi] == '#') {
                        printf("Step blocked! You hit a wall.\n");
                        continue;
                }

                players[index].movesMade++;
                
                
                char tile = map[Ycoordi][Xcoordi];

                // Check for Treasures
                if (tile == 'T') {
                        printf("You found a treasure!! +10 Points!!!\n");
                        players[index].score = players[index].score + 10;
                        players[index].treasuresFound++;
                }

                // Check for Health Packs
                else if (tile == 'H') {
                        printf("You found a Health Pack!! +20 HP!!!\n");
                        players[index].health = players[index].health + 20;
                        players[index].healthPacksUsed++;
                        
                        // limit health to 100
                        if (players[index].health > 100) {
                                players[index].health = 100; 
                        }
                }

                // Check for Keys
                else if (tile == 'K') {
                        printf("You found a Key!!!\n");
                        players[index].keys = players[index].keys + 1;
                        players[index].keysCollected++;
                }

                // Check for Locked Doors
                else if (tile == 'D') {
                        if (players[index].keys > 0) {
                                printf("You used a key to unlock a door!!!\n");
                                players[index].keys = players[index].keys - 1; 
                                players[index].doorsUnlocked++;
                        } else {
                                printf("The door is locked! You need a key to pass\n");
                                continue;
                        }
                }

                // Check for Hidden Traps
                if (hiddenTraps[Ycoordi][Xcoordi] == 1) {
                        printf("You stepped on a hidden trap!! -20 HP!!!\n");
                        players[index].health = players[index].health - 20;
                        players[index].trapsTriggered++;
                        players[index].damageTaken = players[index].damageTaken + 20;
                        hiddenTraps[Ycoordi][Xcoordi] = 0; // remove the trap
                }


                //erase old position
                map[players[index].y][players[index].x] = ' ';

                players[index].x = Xcoordi; 
                players[index].y = Ycoordi;

                //new position
                map[players[index].y][players[index].x] = players[index].symbol;
        }       

}

// check if all treasures are collected
int checkWin() {
        int treasuresLeft = 0;
        for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                        if (map[i][j] == 'T') {
                                treasuresLeft++;
                        }
                }
        }
        
        if (treasuresLeft == 0) {
                return 1; 
        } else {
                return 0; 
        }
}

// check if all players are dead
int checkLoss() {
        int lostPlayers = 0;
        for (int i = 0; i < totalActivePlayers; i++) {
                if (players[i].health <= 0) {
                        lostPlayers++;
                }
        }

        if (lostPlayers == totalActivePlayers) {
                return 1;
        } else {
                return 0;
        }
}

void displayLeaderboard() {
        printf("\n\n********************************\n");
        printf("             LEADERBOARD            \n");
        printf("\n**********************************\n");

        //to identify who the winner is
        int maxScore = -1;

        for (int i = 0; i < totalActivePlayers; i++) {
                
                int finalScore = players[i].score;

                //calculate HP bonus
                if (players[i].health > 0) {
                        int hpBonus = players[i].health / 2;
                        finalScore = finalScore + hpBonus;
                        printf("Player %c survived! HP Bonus: +%d points\n", players[i].symbol, hpBonus);
                } else {
                        printf("Player %c lost. No HP bonus.\n", players[i].symbol);
                }

                // check the highest score
                if (finalScore > maxScore) {
                        maxScore = finalScore;
                }
                
                // Save the final score to the struct
                players[i].score = finalScore; 

                //player's stats
                printf("\n-------------------------------\n");
                printf("------- PLAYER %c STATS --------\n", players[i].symbol);
                printf("Final Score:     %d\n", finalScore);
                printf("Moves Made:      %d\n", players[i].movesMade);
                printf("Treasures Found: %d\n", players[i].treasuresFound);
                printf("Traps Triggered: %d\n", players[i].trapsTriggered);
                printf("Damage Taken:    %d\n", players[i].damageTaken);
                printf("Health Packs:    %d\n", players[i].healthPacksUsed);
                printf("Keys Collected:  %d\n", players[i].keysCollected);
                printf("Doors Unlocked:  %d\n", players[i].doorsUnlocked);
        }

        
        printf("\n----------------------------------\n");
        
        for (int i = 0; i < totalActivePlayers; i++) {
                if (players[i].score == maxScore) {
                        printf("** PLAYER %c WINS!! **\n", players[i].symbol);
                }
        }

        printf("------------------------------\n\n");
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


//file Save / Load

void saveGame() {
        //open a file called "savegame.dat" to save
        FILE *file = fopen("savegame.dat", "wb");
        
        if (file == NULL) {
                printf("Error: Could not save the game!\n");
                return;
        }

        //write the data of map, traps and players to the file
        fwrite(map, sizeof(char), 15 * 15, file);
        fwrite(hiddenTraps, sizeof(int), 15 * 15, file);
        fwrite(players, sizeof(Player), 3, file); //updated to 3
        fwrite(&totalActivePlayers, sizeof(int), 1, file);
        fwrite(&currentRound, sizeof(int), 1, file);

        fclose(file);
        printf("\n***  Game Saved Successfully!!  ***\n");
}

void loadGame() {
        // Open the file to load
        FILE *file = fopen("savegame.dat", "rb");
        
        if (file == NULL) {
                printf("No saved game found! Starting a new game...\n");
                initializeMap();
                return;
        }

        //read the data directly back into the arrays
        fread(map, sizeof(char), 15 * 15, file);
        fread(hiddenTraps, sizeof(int), 15 * 15, file);
        fread(players, sizeof(Player), 3, file); // Updated to 3
        fread(&totalActivePlayers, sizeof(int), 1, file);
        fread(&currentRound, sizeof(int), 1, file);
        
        fclose(file);
        printf("\n***  Game Loaded Successfully!!  ***\n");
}

int main() {
	srand(time(NULL));
	
        //Main menu
        int choice;
        printf("---------------------------------\n");
        printf("         TREASURE HUNT           \n");
        printf("---------------------------------\n");
        printf("1. Start New Game\n");
        printf("2. Load Saved Game\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);

        if (choice == 2) {
                loadGame();
        }
        else {
                //for part B
                printf("Enter number of players (1-3): ");
                scanf("%d", &totalActivePlayers);

                if (totalActivePlayers < 1 || totalActivePlayers > 3) {
                        printf("Invalid choice. Set default for 2 players.\n");
                        totalActivePlayers = 2; 
                }

                initializeMap();
        }

        int gameIsRunning = 1;
        int currentPlayerIndex = 0; // start with player 1

        while (gameIsRunning == 1) {

                //check if a player has won by getting all treasures
                if (checkWin() == 1) {
                        printf("\n\n-----------------------\n");
                        printf("     YOU WIN !!!     \n");
                        printf("\n-----------------------\n");
                        gameIsRunning = 0;
                        break;
                }

                //check if all players have lost
                if (checkLoss() == 1) {
                        printf("\n\n-------------------------\n");
                        printf("   ALL PLAYERS DIED! GAME OVER!\n");
                        printf("\n---------------------------\n");
                        gameIsRunning = 0;
                        break;
                }

                printf("\n\n-------------------------\n");
                printf("           NEXT Player         \n");
                printf("\n-------------------------\n");

                //skip turns of lost players
                if (players[currentPlayerIndex].health <= 0) {
                        printf("Player %c has lost and skips their turn!\n", players[currentPlayerIndex].symbol);
                        
                        //switch players and go to the next turn
                        currentPlayerIndex++;

                        if (currentPlayerIndex >= totalActivePlayers) {
                                currentPlayerIndex = 0;
                                currentRound++;
                        }
                        continue;
                }

                printMap();
                
                movePlayer(currentPlayerIndex);
                currentPlayerIndex++;
                if (currentPlayerIndex >= totalActivePlayers) {
                        currentPlayerIndex = 0;
                        currentRound++;   
                }

        }

        displayLeaderboard();

        return 0;
}