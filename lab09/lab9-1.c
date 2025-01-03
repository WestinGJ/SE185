// Lab 09 DS4Talker Skeleton Code       

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses/ncurses.h>
#define WORDLENGTH 11
#define MAXWORDS 100
#define DEBUGM 1   // Set this to 0 to disable debug output

// Reads words from the file into WL and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int read_words(char* WL[MAXWORDS], char* file_name);

// modifies str to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* str);

void draw_character(int x, int y, char use);

void scan_controller(int time, int triangle, int circle, int x, int square, int jButtonR, int jButtonL,
	int options, int share, int R2, int L2, int R1, int L1, int Lj1, int Lj2, int Rj1, int Rj2);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordcount;
	int i;
	int rows = 0, cols = 0;
	int yVal = 0, xVal = 0;
	int yCurr = 0, xCurr = 10, xOld = 10, yOld = 0;
	int time;
	int triangle, circle, x, square;
	int jButtonR, jButtonL, options, share, R2, L2, R1, L1;
	int Lj1, Lj2, Rj1, Rj2;
	int waitTime = 0;
	int rowCount;
	int lengthOfLast = 0;
	int lengthOfSentence = 0;
	int capitalizeNext = 0;
	
	
	
	wordcount = read_words(wordlist, argv[1]);
	rowCount = wordcount/5;

	if (DEBUGM) {
		printf("Read %d words from %s \n", wordcount, argv[1]);
		for (i = 0; i < wordcount; i++) {
			printf("%s,", wordlist[i]);

		}
		printf("\n");
	}

	// most of your code goes here. Do not forget to include the ncurses library 
	
	//prints word list to screen
	initscr();
	refresh();
	
	for(i = 0; i < wordcount; i++)
	{
		mvprintw(yVal, xVal, "%.15s", wordlist[i]);
		refresh();
		xVal += 15;
			
		if(xVal >= 75)
		{
			yVal++;
			xVal = 0;
		}
	}	
	if(wordcount%rowCount != 0)
	{
		++rowCount;
	}
	
	while(1){
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", 
				&time, &triangle, &circle, &x, &square, &jButtonR, &jButtonL,
				&options, &share, &R2, &L2, &R1, &L1, &Lj1, &Lj2, &Rj1, &Rj2);
		
		if(time - waitTime < 200)
		{
			continue;
		}
		
		draw_character(xOld, yOld, ' ');
		
		if((Rj1 > 100) && (yCurr < rowCount - 1))
		{
			xCurr += 15;
		}
		if((Rj1 < -100) && (xCurr > rowCount - 1))
		{
			xCurr -= 15;
		}
		if((Rj2 > 100) && (yCurr < rowCount - 1))
		{
			yCurr++;
		}
		if((Rj2 < -100) && (xCurr > rowCount - 1))
		{
			yCurr--;
		}
		waitTime = time;
		xOld = xCurr;
		yOld = yCurr;
		draw_character(xCurr, yCurr, '<');
		
		if(triangle == 1) //Add selected word with appended space
		{
				int indexToUse = yCurr*5 + xCurr/15;
				lengthOfLast = strlen(wordlist[indexToUse])+1;
				
				char toAdd[12];
				strcpy(toAdd, wordlist[indexToUse]);
				if(capitalizeNext)
				{
					toAdd[0] -= 0x20;
				}
				mvprintw(rowCount+2, lengthOfSentence, "%s", toAdd);
				lengthOfSentence += lengthOfLast;
		}
		else if(x == 1) //Remove the last item
		{
			int indexToUse = yCurr*5 + xCurr/15;
			lengthOfSentence -= lengthOfLast;
		}
		else if(square == 1) //Add selected word without a space
		{
			int indexToUse = yCurr*5 + xCurr/15;
			lengthOfLast = strlen(wordlist[indexToUse]);
			char toAdd[12];
			strcpy(toAdd, wordlist[indexToUse]);
			if(capitalizeNext)
			{
					toAdd[0] -= 0x20;
			}
			mvprintw(rowCount+2, lengthOfSentence, "%s", toAdd);
			lengthOfSentence += lengthOfLast;
			
		}
		else if(circle == 1) //Add selected word with capitalized first letter
		{
			if(capitalizeNext)
			{
				capitalizeNext = 0;
				mvprintw(rowCount+1, 0,"    ");
			}
			else 
			{
				capitalizeNext = 1;
				mvprintw(rowCount+1, 0,"CAP");
			}
		
		}
	}

	return 0;
}

// DO NOT MODIFY THIS FUNCTION!
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


// DO NOT MODIFY THIS FUNCTION!
int read_words(char* WL[MAXWORDS], char* file_name)
{
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

void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void scan_controller(int time, int triangle, int circle, int x, int square, int jButtonR, int jButtonL,
	int options, int share, int R2, int L2, int R1, int L1, int Lj1, int Lj2, int Rj1, int Rj2)
{
	scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", 
				&time, &triangle, &circle, &x, &square, &jButtonR, &jButtonL,
				&options, &share, &R2, &L2, &R1, &L1, &Lj1, &Lj2, &Rj1, &Rj2);
}