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
#include <math.h>

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int a;
	a = 6427 + 1725;
	printf("6427 + 1725 = %d", a);
	
	int b;
	b = (6971 * 3925) - 95;
	printf("\n(6971 * 3925) - 95 = %d", b);
	
	double c;
	c = 79 + 12 / 5;
	printf("\n79 + 12 / 5 = %.2lf" , c);
	
	double d;
	d = 3640.0 / 107.9;
	printf("\n3640.0 / 107.9 = %.2lf", d);
	
	int e;
	e = (22 / 3) * 3;
	printf("\n(22 / 3) * 3 = %d", e);
	
	int f;
	f = 22 / (3 * 3);
	printf("\n22 / (3 * 3) = %d", f);
	
	double g;
	g = 22 / (3 * 3);
	printf("\n22 / (3 * 3) = %.2lf", g);
	
	double h;
	h = 22 /  3 * 3;
	printf("\n22 /  3 * 3 = %.2lf", h);
	
	double i;
	i = (22.0 / 3) * 3.0;
	printf("\n(22.0 / 3) * 3.0 = %.2lf", i);
	
	int j;
	j = 22.0 / (3 * 3.0);
	printf("\n22.0 / (3 * 3.0) = %d", j);
	
	double k;
	k = 22.0 / 3.0 * 3.0;
	printf("\n22.0 / 3.0 * 3.0 = %.2lf", k);
	
	double l;
	// Area of Circle = Pi * ((Circumference/2Pi)^2)
	l = 3.14159 * pow( (23.567 / (2 * 3.14159)) , 2);
	printf("\nArea of circle with circumference 23.567 = %.2lf", l);
	
	double m;
	//Feet to meters = meters * 0.3
	m = 14 * 0.3;
	printf("\n14 ft. = %.2lf m", m);
	
	double n;
	//Fahrenheit to Celsius = (Fahrenheit - 32) / 18
	n = (76 - 32) / 18;
	printf("\n76 degrees Fahrenheit = %.2lf degrees Celsius", n);

    return 0;
}
