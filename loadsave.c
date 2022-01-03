#include "loadsave.h"


void saveGame(struct cell **grid)
{
	FILE* f = fopen("savefile.bin", "wb");
	if (f == NULL) {
		printf("Error: File not opened for writing.\n");
	}
		for (int i = 0; i < GRID_HEIGHT; i++)
			for (int j = 0; j < GRID_WIDTH; j++)
				fwrite(&grid[i][j], sizeof(grid), 1, f);
	fclose(f);
}

int checkSaveFile()
{
	FILE* f = fopen("savefile.bin", "rb");
	if (f == NULL) {
		return 0;
	} else return 1;
}

//loads game file
void loadGame()
{
	// grid array
	struct cell **grid;

	// loop
	int gameover = 0;

	// user input
	int inputX;
	int inputY;
	int firstInput = 0;
	int generateCounter = 0;

	// create the grid
	// set up dynamic array
	grid = malloc(GRID_HEIGHT * sizeof(struct cell*));
	for (int row = 0; row < GRID_HEIGHT; row++) {
		grid[row] = malloc(GRID_WIDTH * sizeof(struct cell));
	}
	
	
	

	FILE * f = fopen("savefile.bin", "rb"); //this must work because I already checked  (function:  saveFileCheck())
	
	
	//read data from file to struct array grid element by element
	for (int i = 0; i < GRID_HEIGHT; i++)
		for (int j = 0; j < GRID_WIDTH; j++)
			fread(&grid[i][j], sizeof(grid), 1, f);

	fclose(f);
	
	

	while (!gameover) {
		// display grid
		displayGrid(grid);

		// ask for user input x
		do {
			printf("Enter X: ");
			inputX = getch() - '0';
			printf("%c\n",inputX + '0');
			if(inputX == 67) //thats the s symbol (115 - 48 = 67)
			{
				printf("\nSaving...\n");
				saveGame(grid);
			}

		} while (inputX >= GRID_WIDTH || inputX < 0);

		// ask for user input y
		do {
			printf("Enter Y: ");
			inputY = getch() - '0';
			printf("%c\n",inputX);
			if(inputX == 67) //that the s symbol (115 - 48 = 67)
			{
				printf("\nSaving...\n");
				saveGame(grid);
			}

		} while (inputY >= GRID_HEIGHT || inputY < 0);


		// reveal the cell if the coord is correct
		if (grid[inputY][inputX].role != CELL_MINE) {
			grid[inputY][inputX].reveal = SHOW;

			// if blank cell
			if (grid[inputY][inputX].role == CELL_BLANK) {
				sweepGrid(grid, inputX, inputY);
			}
			else {

			}
		}
		else {
			flipGrid(grid);
			displayGrid(grid);
			printf("Game over: You hit a bomb!!\n");
			system("pause");
			gameover = 1;
			drawMainMenu();
			menuEventHandler();
		}

		// check win
		if (checkWin(grid) && ! gameover) {

			flipGrid(grid);
			displayGrid(grid);
			printf("You win!\n");
			system("pause");
			gameover = 1;
			drawMainMenu();
			menuEventHandler();
		}
	}

	// free memory
	for (int i = 0; i < GRID_HEIGHT; i++) {
		free(grid[i]);
	}
	free(grid);
}
