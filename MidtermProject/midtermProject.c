/*----------------------------------------------------------------------------
-		         SE 185: Midterm Project   	              					 -
-	Name: Westin Gjervold													 -
- 	Section: 5																 -
-	NetID: westing														     -
-	Date: 10/04/2022  														 - 
- 																			 -	
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <String.h>

/*----------------------------------------------------------------------------
-	                            Functions Prototypes                         -
-----------------------------------------------------------------------------*/
double Average(double attempts, double finalScore);

/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc midtermProject.c -o midtermProject.exe
// Run with ./midtermProject

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main()
{
	//Declaring Variables
	int attemptsQuiz1, attemptsQuiz2, attemptsQuiz3;
	double currentScoreQuiz1, currentScoreQuiz2, currentScoreQuiz3;
	double finalScoreQuiz1, finalScoreQuiz2, finalScoreQuiz3;
	int luckyNumber;
	int quizNumber;
	int completedQuiz1, completedQuiz2, completedQuiz3 = 0;
	char answer1Quiz1[6], answer1Quiz2[6], answer1Quiz3[6];
	char answer2Quiz1, answer2Quiz2, answer2Quiz3;
	char answer3Quiz1[6], answer3Quiz2[6], answer3Quiz3[6];
	
	//Intro Message + Picks Random Quiz
	printf("Welcome to Quiz Me!\n");
	printf("There are three quizzes (Quiz 01, Quiz 02, Quiz 03)\n");
	while( !(luckyNumber>0 && luckyNumber<10) ){
		printf("Enter your lucky number (1-9): ");
		scanf("%d", &luckyNumber);
	}
	srand(luckyNumber*1000);
	quizNumber = (rand() % 3) + 1;
	
	//Quiz Loop
	while(quizNumber < 4 && quizNumber > 0){
		//Quiz 1
		if(quizNumber == 1){	
			currentScoreQuiz1 = 0;
			printf("\nQuiz #1\n");		
			while(completedQuiz1 != 1){
				//Question 1
				printf("1) Is '1stVariable' a valid variable name?\n");
				printf("Enter 'True' or 'False': ");
				scanf("%s", &answer1Quiz1);
				if(strcmp(answer1Quiz1, "False") == 0){
					printf("Correct\n");
					currentScoreQuiz1 += 5;
				}
				else{
					printf("Incorrect\n");
				}
				
				//Question 2 
				printf("\n2) What is the output of the following code?\n");
				printf("int i = 0;\n");
				printf("printf(\"%%s\", i++);\n");
				printf("a. 0\n");
				printf("b. 1\n");
				printf("c. 2\n");
				printf("d. (null)\n");
				printf("Answer (a, b, c, or d): ");
				scanf(" %c", &answer2Quiz1);
				if(answer2Quiz1 == 'd'){
					printf("Correct\n");
					currentScoreQuiz1 += 5;
				}
				else{
					printf("Incorrect\n");
				}
				
				//Question 3
				printf("\n3) What is the output of the following code?\n");
				printf("int i = 5;\n");
				printf("i = pow(i,2);\n");
				printf("printf(\"%%d\", i);\n");
				printf("Answer: ");
				scanf("%s", &answer3Quiz1);
				if(strcmp(answer3Quiz1, "25") == 0){
					printf("Correct\n");
					currentScoreQuiz1 += 5;
				}
				else{
					printf("Incorrect\n");
				}
				
				//Check if all answers are correct
				finalScoreQuiz1 += currentScoreQuiz1;
				attemptsQuiz1++;
				if(currentScoreQuiz1 == 15){
					printf("\nScore for Quiz 1: %.0lf%%\n", Average(attemptsQuiz1, finalScoreQuiz1));
					completedQuiz1 = 1;
				}
				else{
					printf("\nScore for Quiz 1: %.0lf%%\n", Average(attemptsQuiz1, finalScoreQuiz1));
			}
		}
	}

		//Quiz 2 
		if(quizNumber == 2){			
			while(completedQuiz2 != 1){
				currentScoreQuiz2 = 0;
				printf("\nQuiz #2\n");
				
				//Question 1
				printf("1) Is the following a correct way to declare two ints on one line?\n");
				printf("int i,j;\n");
				printf("Enter 'True' or 'False': ");
				scanf("%s", &answer1Quiz2);
				if(strcmp(answer1Quiz2, "True") == 0){
					printf("Correct\n");
					currentScoreQuiz2 += 5;
				}
				else{
					printf("Incorrect\n");
				}
			
				//Question 2 
				printf("\n2) How many ints can be stored in this 2-D array?\n");
				printf("int number[5][10];\n");
				printf("a. 5\n");
				printf("b. 10\n");
				printf("c. 15\n");
				printf("d. 50\n");
				printf("Answer (a, b, c, or d): ");
				scanf(" %c", &answer2Quiz2);
				if(answer2Quiz2 == 'd'){
					printf("Correct\n");
					currentScoreQuiz2 += 5;
				}
				else{
					printf("Incorrect\n");
				}
			
				//Question 3
				printf("\n3) What is the output?\n");
				printf("int i = 8/6;\n");
				printf("printf(\"%%d\", i);\n");
				printf("Answer: ");
				scanf("%s", &answer3Quiz2);
				if(strcmp(answer3Quiz2, "1") == 0){
					printf("Correct\n");
					currentScoreQuiz2 += 5;
				}
				else{
					printf("Incorrect\n");
				}
			
				//Check if all answers are correct
				finalScoreQuiz2 += currentScoreQuiz2;
				attemptsQuiz2++;
				if(currentScoreQuiz2 == 15){
					printf("\nScore for Quiz 2: %.0lf%%\n", Average(attemptsQuiz2, finalScoreQuiz2));
					completedQuiz2 = 1;
				}
				else{
					printf("\nScore for Quiz 2: %.0lf%%\n", Average(attemptsQuiz2, finalScoreQuiz2));
				}
			}
		}

		//Quiz 3
		if(quizNumber == 3){			
			while(completedQuiz3 != 1){
				currentScoreQuiz3 = 0;
				printf("\nQuiz #3\n");
			
				//Question 1
				printf("1) The range of an int is -32,768 to 32,768.\n");
				printf("Enter 'True' or 'False': ");
				scanf("%s", &answer1Quiz3);
				if(strcmp(answer1Quiz3, "True") == 0){
					printf("Correct\n");
					currentScoreQuiz3 += 5;
				}
				else{
					printf("Incorrect\n");
				}
				
				//Question 2 
				printf("\n2) How many times will this loop repeat itself?\n");
				printf("for(int i = 0; i < 10; i++);\n");
				printf("a. 9\n");
				printf("b. 10\n");
				printf("c. 11\n");
				printf("d. 0\n");
				printf("Answer (a, b, c, or d): ");
				scanf(" %c", &answer2Quiz3);
				if(answer2Quiz3 == 'b'){
					printf("Correct\n");
					currentScoreQuiz3 += 5;
				}
				else{
					printf("Incorrect\n");
				}
			
				//Question 3
				printf("\n3) What is the output of the following code?\n");
				printf("if(1 && 0){\n");
				printf("	printf(\"A\");\n");
				printf("}\n");
				printf("else if(1 || 0){\n");
				printf("	printf(\"B\");\n");
				printf("}\n");
				printf("else{\n");
				printf("	printf(\"C\");\n");
				printf("}\n");
				printf("Answer: ");
				scanf("%s", &answer3Quiz3);
				if(strcmp(answer3Quiz3, "B") == 0){
					printf("Correct\n");
					currentScoreQuiz3 += 5;
				}
				else{
					printf("Incorrect\n");
				}
			
				//Check if all answers are correct
				finalScoreQuiz3 += currentScoreQuiz3;
				attemptsQuiz3++;
				if(currentScoreQuiz3 == 15){
					printf("\nScore for Quiz 3: %.0lf%%\n", Average(attemptsQuiz3, finalScoreQuiz3));
					completedQuiz3 = 1;
				}
				else{
					printf("\nScore for Quiz 3: %.0lf%%\n", Average(attemptsQuiz3, finalScoreQuiz3));
				}
			}
		}
		
		//Prompts user to take another quiz or exit
		printf("\nWould you like to take another quiz?\n");
		printf("If you would like to continue, please enter the quiz number (Ex: 1, 2, or 3).\n");
		printf("If you would like to exit enter the number 0.\n");
		printf("Answer: ");
		scanf("%d", &quizNumber);
	}

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
double Average(double attempts, double finalScore){
	double avgScore;
	avgScore = (finalScore / (attempts*15)) * 100;
	return avgScore;
}



