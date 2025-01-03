//SE 185: Final Project 
//Typing Game
//"Westin Gjervold" | "100%"

//Heeader Files and Constant Variables//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses/ncurses.h>
#include <time.h>
#include <ctype.h>
#define MAXWORDS 2000
#define WORDLENGTH 17
#define EMPTY_SPACE ' '

//User Defined Functions Prototype//
void draw_character(int x, int y, char use);
void window_outline();
int read_words(char* WL[MAXWORDS], char* file_name);
void trimws(char* str);

//Main function
int main(int argc, char* argv[]) {
	//Declaring variables
	int wordcount;
	int rows = 0, cols = 0;
	int yVal[MAXWORDS], xVal[MAXWORDS];
	int timePassed;
	int gameOver;
	int numBoardWords;
	int randWord;
	int rand_X_Value;
	int temp_Y_Value;
	char boardWords[MAXWORDS][WORDLENGTH];
	char empty_space[17] = "                 ";
	char answer[20];
	char startOption;
	char wordAdded[20];
	char* wordlist[MAXWORDS];
	char* file_name = argv[1];
	time_t startTime, endTime;
	//Seeds random time
	srand(time(0));
	//Counts the number of words in the file and puts them into an array
	wordcount = read_words(wordlist, file_name);
	//Start message
	printf("Hello, this is the typing game. You will need to type the words as they appear\n");
	printf("Would you like to play or add a word?\n");
	printf("You currently have %d words that can be used. (p/w)\n", wordcount);
	//Infinite loop
	while(1){
		//Gets start option from user
		scanf("%c", &startOption);
		//If w is selected
		while(startOption == 'w'){
			FILE *wordList = fopen("wordList.txt", "a+");
			printf("What word would you like to add?\n");			
			scanf("%s", wordAdded);	
			fprintf(wordList, "\n%s", wordAdded);
			fclose(wordList);
			wordcount = read_words(wordlist, file_name);
			printf("There are now %d words. Would you like to play or add a word?(p/w)\n", wordcount);
			break;
		}
		//If p is selected
		while(startOption == 'p'){
			//Sets up the screen
			initscr();
			refresh();
			window_outline();
			gameOver = 0;
			numBoardWords = 0;
			//Sets all the y values to 1
			for(int i; i <= MAXWORDS; i++){
				yVal[i] = 1;
			}
			//Game loop
			while(gameOver == 0){
				//Prints the words on the board
				for(int i = 0; i <= numBoardWords; i++){
					if(strcmp(boardWords[i], "") == 0){
						randWord = rand() % (wordcount+1);
						rand_X_Value = (rand()%30) + 1;
						xVal[i] = rand_X_Value;
						strcpy(boardWords[i], wordlist[randWord]);
					}
					mvprintw(yVal[i], xVal[i], "%s", boardWords[i]);
				}
				//Gets user input and checks the time passed
				mvprintw(21, 0, "Type here: ");
				time(&startTime);
				getstr(answer);
				time(&endTime);
				timePassed = difftime(endTime, startTime);
				//Checks if user is correct
				for(int i = 0; i <= numBoardWords; i++){
					if(strcmp(boardWords[i], answer) == 0){
						strcpy(boardWords[i], " ");
						mvprintw(21, 11, "%s", empty_space);
					}
					if(strcmp(boardWords[i], answer) != 0){
						mvprintw(21, 11, "%s", empty_space);
					}
					mvprintw(yVal[i], xVal[i], "%s", empty_space);
				}
				//Increases the number of words on the board
				numBoardWords += timePassed;
				//Changes the y values and check if the bottom is touched
				temp_Y_Value = numBoardWords+1;
				for(int i = 0; i <= numBoardWords; i++){
					if(strcmp(boardWords[i], " ") != 0){
						yVal[i] = temp_Y_Value;
						if(yVal[i] > 18){
							gameOver = 1;
						}
					}
					temp_Y_Value--;
				}
			}
			if(gameOver == 1){
				startOption = '!';
			}
		endwin();
		}
		//End message
		if(startOption == '!'){
			printf("A word touched the bottom!\n");
			printf("You made it %d seconds!\n", numBoardWords);
			break;
		}
	}
	return 0;
}

//User Defined Functions' Definition//

//Draws a character in the screen
void draw_character(int x, int y, char use){
	mvaddch(y,x,use);    
	refresh();
}

//Draws the window outline
void window_outline(){
	int row = 0;
	int column = 0;
	for(int i = 0; i < 51; i++){
			draw_character(i, row, '_');
	}
	row++;
	for(row = 1; row < 19; row++){
		draw_character(0, row, '|');
		draw_character(50, row, '|');
	}
	for(int i = 0; i < 51; i++){
		draw_character(i, row, '_');
	}
	row++;
	for(int i = 0; i < 51; i++){
		draw_character(i, row, '_');
	}
}

//Reads the words in the file and returns the number of words	
int read_words(char* WL[MAXWORDS], char* file_name){
	int numread = 0;
	char line[WORDLENGTH];
	char *p;
	FILE* fp = fopen(file_name, "r");
	while (!feof(fp)) {
		p = fgets(line, WORDLENGTH, fp);
		if (p != NULL) 
		{
			trimws(line);
			WL[numread] = (char *)malloc(strlen(line) + 1);
			strcpy(WL[numread], line);
			numread++;
		}
	}
	fclose(fp);
	return numread;
}	

//Seperates the words on the same line
void trimws(char* str) {
	int length = strlen(str);
	int x;
	if (length == 0) return;
	x = length - 1;
	while (isspace(str[x]) && (x >= 0)) {
		str[x] = '\0';
		x -= 1;
	}
}	