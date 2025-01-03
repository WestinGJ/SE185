/*----------------------------------------------------------------------------
-		        SE 185: Lab 02 - Solving Simple Problems in C	    	 	 -
-	Name: Westin Gjervold													 -
- 	Section: 5																 -
-	NetID: westing															 -
-	Date: 9/6/22															 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>   // Google this header file to learn more! :)

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    double a, b, c;
    double filler;

    /* Put your code after this line */
	printf("Enter the length of one side of the triangle: ");
	scanf("%lf", &a);
	printf("Enter the length of another side of the triangle: ");
	scanf("%lf", &b);
	
	c = pow(a,2) + pow(b,2);

    /* This next line will calculate the square root of whatever value is
     * inside the parenthesis and assigns it to the variable filler. */
    filler = sqrt(c);
	printf("The length of the other side is %lf", filler);

    return 0;
}
