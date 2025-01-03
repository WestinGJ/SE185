/*----------------------------------------------------------------------------
-		                    SE 185: Lab 06 - Bop-It!	    	             -
-	Name: Westin Gjervold													 -
- 	Section: 5																 -
-	NetID: westing														     -
-	Date: 10/11/2022														 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <String.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
char* RandButton();

/*----------------------------------------------------------------------------
-	                            Notes                                        -
-----------------------------------------------------------------------------*/
// Compile with gcc lab06.c -o lab06.exe
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -t -b | ./lab06

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	//Declaring Variables 
	int buttonNumber;
	int controllerTime, circle, x, square, triangle;
	int responseTime = 2500;
	int limitTime, waitTime;
	int rounds = 0;
	int runGame = -1;
	char button[10];
	
	srand(time(NULL)); /* This will ensure a random game each time. */
	//Welcome Message
	printf("This is a Bop-It Game!\n");
	printf("Please press the Circle Button to begin!\n");
	//Program Loop
	while(1){
		scanf("%d, %d, %d, %d, %d", &controllerTime, &triangle, &circle, &x, &square);
		//Starts game if circle is pressed
		if(circle == 1){
			runGame = 1;
		}
		//Game Loop
		while(runGame == 1){
			scanf("%d, %d, %d, %d, %d", &controllerTime, &triangle, &circle, &x, &square);
			//Waits 300 milliseconds
			waitTime = controllerTime + 300;
			while(waitTime>controllerTime){
				scanf("%d, %d, %d, %d, %d", &controllerTime, &triangle, &circle, &x, &square);
				triangle, circle, x, square = 0;
			}
			//Generates random button
			char *button = RandButton();
			//Generates time user has to answer
			limitTime = controllerTime + responseTime;
			//Prints the button to be pressed and how long user has to do so
			printf("\nPress the %s button!\n", button);
			printf("You have %d milliseconds to respond!\n", responseTime);
			//Loop to check if user exceeds time
			while(limitTime >= controllerTime){
				scanf("%d, %d, %d, %d, %d", &controllerTime, &triangle, &circle, &x, &square);
				//If user is to press triangle
				if(strcmp("triangle",button) == 0){
					//If triangle is pressed
					if(triangle == 1){
						responseTime -= 100;
						rounds++;
						break;
					}
					//If circle is pressed
					if(circle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
						
					}
					//If x is pressed
					if(x == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
					//If square is pressed
					if(square == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
				}
				//If user is to press circle
				else if(strcmp("circle",button) == 0){
					//If circle is pressed
					if(circle == 1){
						responseTime -= 100;
						rounds++;
						break;
					}
					//If triangle is pressed
					else if(triangle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
						
					}
					//If x is pressed
					else if(x == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
					//If square is pressed
					else if(square == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
				}
				//If user is to press x
				else if(strcmp("x",button) == 0){
					//If x is pressed
					if(x == 1){
						responseTime -= 100;
						rounds++;
						break;
					}
					//If circle is pressed
					else if(circle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
						
					}
					//If triangle is pressed
					else if(triangle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
					//If square is pressed
					else if(square == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
				}
				//If user is to press square 
				else if(strcmp("square",button) == 0){
					//If square is pressed
					if(square == 1){
						responseTime -= 100;
						rounds++;
						break;
					}
					//If circle is pressed
					else if(circle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
						
					}
					//If x is presseds
					else if(x == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
					//If triangle is pressed
					else if(triangle == 1){
						printf("\nWrong button!:(\n");
						runGame = 0;
						break;
					}
				}
			}
			//If user exceeds time limit
			if(limitTime < controllerTime){
				printf("\nYou ran out of time!:(\n");
				runGame = 0;
				break;
			}	
		}
		//Game over 
		if(runGame == 0){
			printf("You lose!\n");
			printf("You made it through %d rounds!\n", rounds);
			break;
		}
	}
    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
//Generates random button
char* RandButton(){
	int buttonNumber = (rand() % 4) + 1;
	if(buttonNumber == 1){
		return "triangle";
	}
	else if(buttonNumber == 2){
		return "circle";
	}
	else if(buttonNumber == 3){
		return "x";
	}
	else if(buttonNumber == 4){
		return "square";
	}
}