/*----------------------------------------------------------------------------
-		    SE 185: Lab 03 - Introduction to the DS4 and Functions	    	 -
-	Name: Westin Gjervold													 -
- 	Section: 5																 -
-	NetID: westing														     -
-	Date: 09/13/2022														 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
int numOfButtons(int t, int c, int x, int s);

/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc lab03-2.c -o lab03-2
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -b | ./lab03-2

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	int t, c, x, s;

    while (1)
    {
		scanf("%d, %d, %d, %d", &t, &c, &x, &s);
		printf("\nNumber of buttons pressed: %d", numOfButtons(t, c, x, s));
		
    }

    return 0;
}

/* Put your functions here, and be sure to put prototypes above. */
int numOfButtons(int t, int c, int x, int s){
	int numOfButtons = 0;
	numOfButtons = t+c+x+s;
	return numOfButtons;
}
