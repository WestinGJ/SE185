//SE 185: Final Project Template//
/////////////////////////
/* 
Team xx (please insert your team number instead of xx)
Team member 1 "Westin Gjervold" | "100%"
Team member 2 "Name" | "Percentage of Contribution to The Project"
Team member 3 "Name" | "Percentage of Contribution to The Project"
Team member 4 "Name" | "Percentage of Contribution to The Project"
*/

////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <ctype.h>

//////////////////////
//Struct Definition//
////////////////////
void draw_character(int x, int y, char use);

/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//tehm below the main function////
/////////////////////////////////

int main(){
	initscr();
	refresh();
	window_outline();
	
	
	
	
	
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void window_outline()
{
	int row = 0;
	int column = 0;
	for(int i = 0; i < 41; i++){
			draw_character(i, row, '_');
	}
	row++;
	for(row = 1; row < 19; row++){
		draw_character(0, row, '|');
		draw_character(40, row, '|');
	}
	for(int i = 0; i < 41; i++){
			draw_character(i, row, '_');
	}
	row++;
	for(int i = 0; i < 41; i++){
			draw_character(i, row, '_');
	}
}
	
		