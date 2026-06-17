#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));

	char map[15][15];
	int hiddenTraps[15][15];

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

	int wallsPlaced = 0;

        while (wallsPlaced < 30) {
                int randomRow = (rand() % 13) + 1;
                int randomCol = (rand() % 13) + 1;

                if (map[randomRow][randomCol] == ' ') {
                        map[randomRow][randomCol] = '#';
                        wallsPlaced++;
                }
        }

	
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

return 0;
}
