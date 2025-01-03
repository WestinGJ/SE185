/*----------------------------------------------------------------------------
-		         SE 185: Lab 05 - Conditionals (What's up?)	    	         -
-	Name: Westin Gjervold													 -
- 	Section: 5																 -
-	NetID: westing														     -
-	Date: 09/27/2022														 -
-----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
-								Includes									 -
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

/*----------------------------------------------------------------------------
-	                            Prototypes                                   -
-----------------------------------------------------------------------------*/
int close_to(double tolerance, double point, double value);
double magnitude(double ax, double ay, double az);
char orientation(double gx, double gy, double gz);
int orientation_change(char oldOrientation, char newOrientation);


/*----------------------------------------------------------------------------
-	                                Notes                                    -
-----------------------------------------------------------------------------*/
// Compile with gcc lab05.c -o lab05
// Run with ./ds4rd.exe -d 054c:05c4 -D DS4_BT -a -g -b | ./lab05

/*----------------------------------------------------------------------------
-								Implementation								 -
-----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	//Declaring variables
    int triangle, circle, x_button, square;
    double ax, ay, az, gx, gy, gz;
	double controllerMagnitude;
	char controllerOrientation = 'n';

	//Infinite Loop
    while (1)
    {
		//Scans acceleration, gyrosphere, and button inputs
		scanf("%lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d",
              &ax, &ay, &az, &gx, &gy, &gz, &triangle, &circle, &x_button, &square);
		//Calulates controller magnitude
		controllerMagnitude = magnitude(ax, ay, az);
		//Checks if magnitude is close to 0
		if(close_to(0.02, 0, controllerMagnitude)){
			//Check if the controller orientation changes
			if(orientation_change(controllerOrientation, orientation(gx,gy,gz))){
				//Gets new controller orientation
				controllerOrientation = orientation(gx,gy,gz);
				//Prints the orientation
				if(controllerOrientation == 'L'){
					printf("Left\n");
				}
				else if(controllerOrientation == 'R'){
					printf("Right\n");
				}
				else if(controllerOrientation == 'T'){
					printf("Top\n");
				}
				else if(controllerOrientation == 'B'){
					printf("Bottom\n");
				}
				else if(controllerOrientation == 'F'){
					printf("Front\n");
				}
				else if(controllerOrientation == 'b'){
					printf("Back\n");
				}
			}
		}
		//Breaks infinite loop if triangle is pressed 
		if (triangle == 1){
			break;
		}	
	}
}

//Checks if value is close to point given tolerance
int close_to(double tolerance, double point, double value){
	if (value > (point - tolerance) && value < (point + tolerance)){
		return 1;
	}
	else{
		return 0;
	}
}

//Calulates and returns magnitude
double magnitude(double ax, double ay, double az){
	double magnitude;
	magnitude = sqrt(pow(ax,2) + pow(ay,2) + pow(az,2));
	return magnitude;
}

//Returns orientation
char orientation(double gx, double gy, double gz){
	if(close_to(0.1, -1 , gx)){
		return 'L';
	}
	else if(close_to(0.1, 1 , gx)){
		return 'R';
	}
	else if(close_to(0.1, 1 , gy)){
		return 'T';
	}
	else if(close_to(0.1, -1 , gy)){
		return 'B';
	}
	else if(close_to(0.1, -1 , gz)){
		return 'F';
	}
	else if(close_to(0.1, 1 , gz)){
		return 'b';
	}
}

//Checks if orientation changes
int orientation_change(char oldOrientation, char newOrientation){
	if (oldOrientation != newOrientation){
		return 1; 
	}
	else{
		return 0;
	}
}


	


	