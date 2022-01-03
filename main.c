#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

//Unit testing
#include <assert.h>

//modules

#include "count.h"
#include "log.h"


//TEMPORARY DELETE THIS WHEN COMPILING
#include "count.c"
#include "log.c"



///////////////////////////////////////////MENU


//GAME OPTIONS (by default)
char * difficulty = "normal";


//UI design chars (based on ASCII codes)
char block = 176;
char angle1 = 201;
char angle2 = 187;
char angle3 = 200;
char angle4 = 188;
char t1 = 204;
char t2 = 185;
char ver = 186;
char hor = 205;

//ASCII  ART
char art[] = "        ,--.!,\n     __/   -*-\n   ,d08b.  '|`\n   0088MM     \n   `9MMP'     \n";
char title[] = "                                                ,--.!,\n /|/|  '     _   _      _  _      _  _       __/   -*-\n/   | /  /) (- _)  ((/ (- (-  /) (- /      ,d08b.  '|`\n                             /             0088MM     \n                                           `9MMP'     \n";

// function prototypes
void drawErrorLoadMenu();
void drawMainMenu();
void menuEventHandler();
void drawOptionsMenu();
void optionsMenuHandler();
void errorLoadMenuHandler();


/////////////////////////////////////////////GAME

// game constants
const int CELL_BLANK = 0;
const int CELL_MINE = -1;

const char BLANK = ' ';
const char MINE = 'X';
const char FLAG = 'P';

const int HIDDEN = 0;
const int SHOW = 1;


// grid properties
const int GRID_WIDTH = 9;
const int GRID_HEIGHT = 9;
int MINES; //This will change when setting difficulty. This is set during launchGame();

// cell structure
struct cell {
	// can be number or mine (0 for blank, -1 for mine)
	int role;

	// can be 0 for hidden, 1 for show, 2 for flag
	int reveal;
};


///function prototypes

void minesweeper();
void clearGrid(struct cell **grid);
void flipGrid(struct cell **grid);
int sweepGrid(struct cell **grid, int startX, int startY);
void placeMines(struct cell **grid);
void placeNumbers(struct cell **grid);
int checkMines(struct cell **grid, int x, int y);
int checkWin(struct cell ** grid);
void displayGrid(struct cell **grid);
void drawLine(int isBorder);
void launchGame();


/////////////////////////////////////////////////////////////////////////////////

//LOADSAVE INCLUDES ARE HERE IN ORDER TO AVOID ERRORS
#include "loadsave.h"
#include "loadsave.c"

int main()
{
    srand(time(NULL));
	system("color 0B");
	system("title Minesweeper");
	logProgramStart();
	drawMainMenu();
	menuEventHandler();
	atexit(logProgramEnd);
	
	
	
	///UNIT TEST 1 UNIT TEST 2 INSIDE FUNCTION MINESWEEPER()
	assert(checkSaveFile() == 1);
	

	

	return 0;
}

void errorLoadMenuHandler()
{
	char keyPress;
	while(1)
	{
		keyPress = _getch();
		if(keyPress == '1')
		{
			drawMainMenu();
			menuEventHandler();
			break;
		}
	}
}

void drawErrorLoadMenu()
{
	system("cls");
	printf("%s",title);
	printf("%c",angle1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",angle2);
	printf("%c   ERROR: SAVE FILE WAS NOT FOUND                 %c\n",ver,ver);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c 1. Back                                          %c\n",ver,ver);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c            Press a number to select!             %c\n",ver,ver);
	printf("%c",angle3);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",angle4);
}

void drawMainMenu()
{
	system("cls");

	printf("%s",title);

	printf("%c",angle1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",angle2);

	printf("%c                     Main Menu                    %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);

	printf("%c 1. Play Game                                     %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);

	printf("%c 2. Load Game                                     %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);

	printf("%c 3. Options                                       %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);

	printf("%c 4. Exit                                          %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);


	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",block);
	}
	printf("%c\n",t2);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}

	printf("%c\n",t2);

	printf("%c            Press a number to select!             %c\n",ver,ver);

	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);

	printf("%c Game project done by: Aurimas Jurgelis INFO 2 gr.%c\n",ver,ver);

	printf("%c",angle3);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n\n",angle4);
	
	
	//Scoreboard
	
	printf("%c",angle1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",angle2);
	
	loadPlayed(&playedCount);

	printf(" Total times played: %d                            \n",playedCount); //insert variable PLAYED

	printf("%c",angle3);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n\n",angle4);
	
	
	
}
void menuEventHandler()
{
	char keyPress;
	while(1)
	{
		keyPress = _getch();
		if(keyPress == '1')
		{
			launchGame();
			break;
		}
		if(keyPress == '2')
		{
			
			if(checkSaveFile())
			{
				loadGame();
			} else {
			drawErrorLoadMenu();
			errorLoadMenuHandler();
			}
			break;
		}
		if(keyPress == '3')
		{
			drawOptionsMenu();
			optionsMenuHandler();
			break;
		}
		if(keyPress == '4')
		{
			break;
		}
	}
}
void optionsMenuHandler()
{
	char keyPress;
	while(1)
	{
		keyPress = _getch();
		if(keyPress == '1')
		{
			//Changes the global string into sth else
			if(difficulty == "normal")
			{
				difficulty = "hard  ";
				drawOptionsMenu();
				continue;
			}
			if(difficulty == "hard  ")
			{
				difficulty = "easy  ";
				drawOptionsMenu();
				continue;
			}
			if(difficulty == "easy  ")
			{
				difficulty = "normal";
				drawOptionsMenu();
				continue;
			}
		}
		if(keyPress == '2')
		{
			//changes the global string into sth else
			drawMainMenu();
			menuEventHandler();
			break;
		}
	}
}

void drawOptionsMenu()
{

	system("cls");
	printf("%s",title);
	printf("%c",angle1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",angle2);
	printf("%c                     Options                      %c\n",ver,ver);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c 1. Difficulty:   %s                          %c\n",ver,difficulty,ver);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c 2. Back                                          %c\n",ver,ver);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",block);
	}
	printf("%c\n",t2);
	printf("%c",t1);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n",t2);
	printf("%c            Press a number to select!             %c\n",ver,ver);
	printf("%c",angle3);
	for (int i = 0; i < 50;i++)
	{
		printf("%c",hor);
	}
	printf("%c\n\n",angle4);
}

void minesweeper() {
	// grid array
	struct cell **grid;

	// loop
	int gameover = 0;

	// user input
	int inputX;
	int inputY;
	int firstInput = 1;
	int generateCounter = 0;

	// create the grid
	// set up dynamic array
	grid = malloc(GRID_HEIGHT * sizeof(struct cell*));
	for (int row = 0; row < GRID_HEIGHT; row++) {
		grid[row] = malloc(GRID_WIDTH * sizeof(struct cell));
	}
	
	//UNIT TEST 2 UNIT TEST 3 IS INSIDE MAIN
	assert(checkWin(grid) == 0);
	
	
	
	
	
	
	
	
	//UNIT TEST 3 UNIT TEST 4 IS INSIDE LOAD GAME
	assert(firstInput == 1);
	


	// reset grid
	clearGrid(grid);

	// place mines
	placeMines(grid);

	// place numbers
	placeNumbers(grid);
	
	//PLAYED COUNT
	savePlayed(playedCount);

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
			printf("%c\n",inputY + '0');
			if(inputY == 67) //that the s symbol (115 - 48 = 67)
			{
				printf("\nSaving...\n");
				saveGame(grid);
			}

		} while (inputY >= GRID_HEIGHT || inputY < 0);

		if (firstInput) {
			// user's first input will always be a blank space
			while (grid[inputY][inputX].role != CELL_BLANK) {
				clearGrid(grid);
				placeMines(grid);
				placeNumbers(grid);
				generateCounter++;

				// break if board can't be generated
				if (generateCounter > 100) {
					printf("Board cannot be generated (generator time out), please change config\n");
					break;
				}
			}

			// sets the invulnerability off
			firstInput = 0;
		}

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

//Completely clears the grid including mines and numbers

void clearGrid(struct cell **grid) {
	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int col = 0; col < GRID_WIDTH; col++) {
			// add blank chars to each element
			grid[row][col].role = CELL_BLANK;

			// set reveal for each cells
			grid[row][col].reveal = HIDDEN;
		}
	}
}

//Completely reveals all cells in current grid

void flipGrid(struct cell **grid) {
	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int col = 0; col < GRID_WIDTH; col++) {
			// set reveal for each cells
			grid[row][col].reveal = SHOW;
		}
	}
}

//Sweep the adjascent blank and number grids
int sweepGrid(struct cell **grid, int startX, int startY) {

	for (int j = startY - 1; j <= startY + 1; j++) {
		for (int i = startX - 1; i <= startX + 1; i++) {

			// check not touching the bounds
			if (j >= 0 && j < GRID_HEIGHT &&
				i >= 0 && i < GRID_WIDTH &&

				// skip starting cells
				(i != startY || j != startX) &&

				// skip show values
				(grid[j][i].reveal == HIDDEN)){


				// recursive reveal
				if (grid[j][i].role == CELL_BLANK) {
					grid[j][i].reveal = SHOW;

					// recursive
					sweepGrid(grid, i, j);

				}
				else if (grid[j][i].role != CELL_MINE) {
					grid[j][i].reveal = SHOW;
				}
				else {
				}
			}
		}
	}
}

//Randomly generates the mines to put all over the place

void placeMines(struct cell **grid) {
	int random_x;
	int random_y;

	for (int i = 0; i < MINES; i++) {
		// generate random values on the XY
		random_x = rand() % GRID_WIDTH;
		random_y = rand() % GRID_HEIGHT;

		// if the space is not already occupied by a mine, then add
		while (grid[random_y][random_x].role == CELL_MINE) {
			// generate more random values until it lands on a free one
			random_x = rand() % GRID_WIDTH;
			random_y = rand() % GRID_HEIGHT;
		}


		// add mine to grid
		grid[random_y][random_x].role = CELL_MINE;
	}
}

// Check each grid and its surroundings for mines Put a number on the cell spot for number of mines around it

void placeNumbers(struct cell **grid) {
	for (int i = 0; i < GRID_HEIGHT; i++) {
		for (int j = 0; j < GRID_WIDTH; j++) {
			if (grid[i][j].role != CELL_MINE) {
				// if the cell is not a mine itself
				grid[i][j].role = checkMines(grid, i, j);
			}
		}
	}
}

//Checks a single location on the grid for number of mines around it

int checkMines(struct cell **grid, int iref, int jref) {
	int count = 0;
	for (int i = iref - 1; i <= iref + 1; i++) {
		for (int j = jref - 1; j <= jref + 1; j++) {
			if (i >= 0 && i < GRID_HEIGHT && j >= 0 && j < GRID_WIDTH && grid[i][j].role == CELL_MINE) {
				count++;
			}
		}
	}
	return count;
}


//Check if the grid is completely "uncovered"
int checkWin(struct cell ** grid) {
	for (int j = 0; j < GRID_HEIGHT; j++) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			if (grid[j][i].reveal == HIDDEN && grid[j][i].role != CELL_MINE) {
				return 0;
			}
		}
	}
	return 1;
}

//Displays the minesweeper grid on the screen

void displayGrid(struct cell **grid) {
	int gridValue;
	int gridShow;

	// clear screen
	system("cls");
	printf("   | Press the s key to save the game! |\n");
	printf("   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	// draw horizontal reference ruler
	printf("   ");
	for (int i = 0; i < GRID_WIDTH; i++) {
		printf(" %2d ", i);
	}
	printf("   X\n");

	// draw horizontal ticks
	printf("   ");
	for (int i = 0; i < GRID_WIDTH; i++) {
		printf("  | ");
	}
	printf("\n");

	// draw grid
	for (int i = 0; i < GRID_HEIGHT; i++) {
		// draw vertical line
		if (!i) {
			drawLine(1);
		}
		else {
			drawLine(0);
		}

		// draw vertical reference ruler
		printf("%2d-", i);

		// draw the cells and vertical separators
		for (int j = 0; j < GRID_WIDTH; j++) {
			gridValue = grid[i][j].role;
			gridShow = grid[i][j].reveal;

			// display different types of cells
			if (gridShow == SHOW) {
				if (gridValue == CELL_BLANK) {
					// blank field
					printf("%c %c ",ver, BLANK);
				}
				else if (gridValue == CELL_MINE) {
					// mine
					printf("%c %c ",ver, MINE);
				}
				else {
					// numbers
					printf("%c %d ",ver, gridValue);
				}
			}
			else if (gridShow == HIDDEN) {
				// hidden cell
				printf("%c - ",ver);
			}
		}
		printf("%c\n",ver);
	}
	// finish the last line
	drawLine(1);
	printf(" Y\n");

}

// draws the line that separates the grid horizontally
void drawFirstLine() {
	printf("   ");
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		printf("%c%c%c%c",angle1,hor,hor,hor);
	}
	printf("%c\n",angle2);
}

void drawLine(int isBorder) {
	printf("   ");
	for (int i = 0; i < GRID_HEIGHT; i++) {
		if (isBorder) {
			if (!i) {
				printf("+%c%c%c",hor,hor,hor);
			}
			else  {
				printf("%c%c%c%c",hor,hor,hor,hor);
			}
		}
		else {
			if (!i) {
				printf("+%c%c%c",hor,hor,hor);
			}
			else {
				printf("+%c%c%c",hor,hor,hor);
			}
		}
	}
	printf("%c\n",'+');
}

//simple launch method
void launchGame()
{
	if(difficulty == "normal") MINES = 10;
	if(difficulty == "hard  ") MINES = 20;
	if(difficulty == "easy  ") MINES = 3;
	minesweeper();
}





