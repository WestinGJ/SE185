/*-----------------------------------------------------------------------------
-					  		SE 185 Lab 08
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Westin Gjervold
- 	Section: 5
-	NetID: Westing
-	Date: 10/25/2022
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <time.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.14159
#define COLUMNS 100
#define ROWS 20
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '
#define NUM_SAMPLES 10

/*-----------------------------------------------------------------------------
-								Static Data
-----------------------------------------------------------------------------*/
char MAZE[COLUMNS][ROWS];

/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
void generate_maze(int difficulty);

void draw_maze(void);

void draw_character(int x, int y, char use);

int calc_roll(double mag);

double m_avg(double buffer[], int avg_size, double new_item);

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
/*	Main - Run with './ds4rd.exe -t -g -b' piped into STDIN */
void main(int argc, char* argv[]){
	//Declaring variables
	int old_X_Avatar = 50;
	int new_X_Avatar = 50;
	int Y_Avatar = 0;
	int difficulty = 0;
	double Xg, Yg, Zg;
	int t, waitTime;
	double x_mag;
	int avg_size = 10;
	double buffer[avg_size];
	int lose = 0;
	sscanf(argv[1], "%d", &difficulty);
	srand((unsigned) difficulty);
	// Setup screen    
	initscr();
	refresh();
	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	draw_character((COLUMNS/2), 0, AVATAR);
	// Read gyroscope data to get ready for using moving averages.    
	scanf("%d, %lf, %lf, %lf", &t, &Xg, &Yg, &Zg);
	// Event loop
	do
	{
		//Read data, update average
		scanf("%d, %lf, %lf, %lf", &t, &Xg, &Yg, &Zg);
		//Is it time to move?  if so, then move avatar
		waitTime = t + 1000;
		//Time delay for Avatar to move
		while(t < waitTime) {	 
			scanf("%d, %lf, %lf, %lf", &t, &Xg, &Yg, &Zg);
			x_mag = m_avg(buffer, avg_size, Xg);
		}
		//Move right
		if(calc_roll(x_mag) == -1){
			new_X_Avatar = old_X_Avatar + 1;
			if(MAZE[new_X_Avatar][Y_Avatar] == WALL){
				lose = 1;
				break;
			}
			else if(MAZE[new_X_Avatar][Y_Avatar] == EMPTY_SPACE){
				draw_character(new_X_Avatar, Y_Avatar, AVATAR);
				draw_character(old_X_Avatar, Y_Avatar, EMPTY_SPACE);
				old_X_Avatar = new_X_Avatar;
			}
		}
		//Move left
		else if(calc_roll(x_mag) == 1){
			new_X_Avatar = old_X_Avatar - 1;
			if(MAZE[new_X_Avatar][Y_Avatar] == WALL){
				lose = 1;
				break;
			}
			else if(MAZE[new_X_Avatar][Y_Avatar] == EMPTY_SPACE){
				draw_character(new_X_Avatar, Y_Avatar, AVATAR);
				draw_character(old_X_Avatar, Y_Avatar, EMPTY_SPACE);
				old_X_Avatar = new_X_Avatar;
			}
		}
		//If Avatar is stuck
		else if((MAZE[old_X_Avatar - 1][Y_Avatar] == WALL) && (MAZE[old_X_Avatar + 1][Y_Avatar] == WALL) && (MAZE[new_X_Avatar][Y_Avatar + 1] == WALL)){
			lose = 1;
			break;
		}
		//If Avatar exceeds boundaries
		if((new_X_Avatar < 0) || (new_X_Avatar > COLUMNS)){
			lose = 1;
			break;
		}
		//Move down
		if(MAZE[new_X_Avatar][Y_Avatar + 1] != WALL){
			Y_Avatar++;
			draw_character(new_X_Avatar, Y_Avatar, AVATAR);
			draw_character(new_X_Avatar, Y_Avatar - 1, EMPTY_SPACE);
		}
	} while(Y_Avatar < ROWS); // Change this to end game at right time 
	//End window and print Win or Lose message
	endwin();
	if (lose == 1){
		printf("YOU LOSE!\n");
	}
	else{
		printf("YOU WIN!\n");
	}
}

//Calculates and returns moving average
double m_avg(double buffer[], int avg_size, double new_item){
	double bufferTotal = 0;
	double bufferAvg = 0;
	for (int i = 0; i < (avg_size - 1); i++){
		buffer[i] = buffer[i+1];
	}
	buffer[avg_size - 1] = new_item;
	for (int i = 0; i < avg_size; i++){
		bufferTotal = bufferTotal + buffer[i];
	}
	bufferAvg = (bufferTotal / avg_size);
	return bufferAvg;
}

//Draws characters 
void draw_character(int x, int y, char use){
    mvaddch(y,x,use);
    refresh();
}

//Generates maze
void generate_maze(int difficulty) {
	int maze_difficulty;
	srand(time(NULL));
	for(int column = 0; column < COLUMNS; ++column){
		for(int row = 0; row < ROWS; ++row){
			maze_difficulty = rand() %100;
			maze_difficulty -= difficulty;
			if (maze_difficulty <= difficulty){
				MAZE[column][row] = WALL;
			}
			else{
				MAZE[column][row] = EMPTY_SPACE;
			}
		}
	}
}

//Draws maze
void draw_maze(void){
	for(int column = 0; column < COLUMNS; ++column) {
		for(int row = 0; row < ROWS; ++row) {
			if (MAZE[column][row] == WALL) {
				draw_character(column, row, WALL);
			}
			else if(MAZE[column][row] == EMPTY_SPACE){
				draw_character(column, row, EMPTY_SPACE);
			}
		}
	}
}

//Calculates and returns roll
int calc_roll(double mag){
	int move;
	if (mag > 0.7){
		move = (-1);
	}
	else if (mag < -0.7){
		move = 1;
	}
	else{
		move = 0;
	}
	return move;
}
