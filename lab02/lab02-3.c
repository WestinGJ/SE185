/*----------------------------------------------------------------------------
-		        SE 185: Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name: Westin Gjervold													 -
- 	Section: 5															     -
-	NetID: Westing														     -
-	Date: 9/6/2022															 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int integer_result;
    double decimal_result;

    integer_result = 77 / 5;
    //printf("The value of 77/5 is %lf, using integer math.\n", integer_result);
	//The variable interger_result is called as a double in the print statement when it is an int
	printf("The value of 77/5 is %d, using integer math.\n", integer_result);
	
    integer_result = 2 + 3;
    //printf("The value of 2+3 is %d.\n");
	//Did not define which variable is used in the print statement
	printf("The value of 2+3 is %d.\n", integer_result);
	
    decimal_result = 1.0 / 22.0;
    //printf("The value 1.0/22.0 is %d.\n", decimal_result);
	//The variable decimal_result is called as an int in the print statement when it is a double
	printf("The value 1.0/22.0 is %lf.\n", decimal_result);
	
    return 0;
}
