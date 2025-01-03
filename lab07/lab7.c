/*-----------------------------------------------------------------------------
-					 SE 185 Lab 07 - The DS4 Equalizer
-             Developed for 185-Rursch by T.Tran and K.Wang
-	Name: Westin Gjervold
- 	Section: 5
-	NetID: Westing
-	Date: 10/18/2022
-
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-								Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------
-								Defines
-----------------------------------------------------------------------------*/
#define PI 3.141592653589

/*-----------------------------------------------------------------------------
-								Prototypes
-----------------------------------------------------------------------------*/
int read_input( int* time,
                double* g_x, double* g_y, double* g_z,
                int* button_T, int* button_C, int* button_X, int* button_S,
                int* l_joy_x, int* l_joy_y, int* r_joy_x, int* r_joy_y );
double scaleMagForScreen(double rad);
int scaleJoyForScreen(int rad);
void graph_line(int number);
void print_chars(int num, char use);

/*-----------------------------------------------------------------------------
-								Implementation
-----------------------------------------------------------------------------*/
int main()
{
	//Declaring Variables
    double x, y, z;                     //Values of x, y, and z axis
    int t;                              //Variable to hold the time value 
    int b_T, b_C, b_X, b_S;  			//Variables to hold the button statuses 
    int j_LX, j_LY, j_RX, j_RY;         //Variables to hold the joystick statuses 
    int scaled_pitch, scaled_roll; 	    //Value of the roll/pitch adjusted to fit screen display
    int scaled_joy;                     //Value of joystick adjusted to fit screen display 
	int graph_char;
	int roll, pitch, joystick = 0;

    /* Put pre-loop preparation code here */
	
    do
    {
        /* Scan a line of input */
		read_input(&t, &x, &y, &z, &b_T, &b_C, &b_X, &b_S, &j_LX, &j_LY, &j_RX, &j_RY);
        /* Calculate and scale for pitch AND roll AND joystick */
		scaled_roll = scaleMagForScreen(x);
		scaled_pitch = scaleMagForScreen(z);
		scaled_joy = scaleJoyForScreen(j_RX);
        /* Switch between roll, pitch, and joystick with the up, down, and right button, respectively */
		if(b_T == 1){
			roll = 1;
			pitch = 0;
			joystick = 0;
		}
		else if(b_C == 1){
			roll = 0;
			pitch = 1;
			joystick = 0;
		}
		else if(b_X == 1){
			roll = 0;
			pitch = 0;
			joystick = 1;
		}
        /* Output your graph line */
		if(roll == 1){
			if(scaled_roll > 0){
				graph_char = 'R';
			}
			else if(scaled_roll < 0){
				graph_char = 'L';
			}
			else if(scaled_roll == 0){
				graph_char = '0';
			}
			graph_line(scaled_roll);
			print_chars(scaled_roll, graph_char);
		}
		else if(pitch == 1){
			if(scaled_pitch > 0){
				graph_char = 'F';
			}
			else if(scaled_pitch < 0){
				graph_char = 'B';
			}
			else if(scaled_pitch == 0){
				graph_char = '0';
			}
			graph_line(scaled_pitch);
			print_chars(scaled_pitch, graph_char);
		}
		else if(joystick == 1){
			if(scaled_joy > 0){
				graph_char = 'R';
			}
			else if(scaled_joy < 0){
				graph_char = 'L';
			}
			else if(scaled_joy == 0){
				graph_char = '0';
			}
			graph_line(scaled_joy);
			print_chars(scaled_joy, graph_char);
		}

        fflush(stdout);
		
    } while(b_S != 1); /* Modify to stop when left button is pressed */

    return 0;

}

//Gets the input of the controllers and points the value to the main function variables
int read_input( int* time, double* g_x, double* g_y, double* g_z, int* button_T, 
	int* button_C, int* button_X, int* button_S, int* l_joy_x, int* l_joy_y,
	int* r_joy_x, int* r_joy_y ) {
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d, %d, %d", time, g_x, g_y, g_z, button_T, button_C, 
		button_X, button_S, l_joy_x, l_joy_y, r_joy_x, r_joy_y);
		return *button_S;
}

//Scales the roll and pitch values to fit an 80-character screen
double scaleMagForScreen(double rad){
	double numChar = -39 * rad;
	if(numChar > 39){
		numChar = 39;
	}
	else if(numChar < -39){
		numChar = -39;
	}
	return numChar;
}

//Scales the Joystick value to fit an 80-character screen
int scaleJoyForScreen(int rad){
	int numChar = 2 * rad;
	numChar += 1;
	numChar = (numChar * 39) / 255;
	return numChar;
}

//Prints the number of spaces necessary to format the graph
void graph_line(int number){
	int spaces = 39 - abs(number);
	if(number < 0){
		for (int i = 0; i < spaces; i++){
			printf(" ");
		}
	}
	else if(number > 0){
		for (int i = 0; i < 40; i++){
			printf(" ");
		}
	}
	else{
		for (int i = 0; i < 39; i++){
			printf(" ");
		}
	}	
}

//Prints the number of characters to print on the graph
void print_chars(int num, char use){
	for (int i = 0; i < abs(num); i++){
		printf("%c", use);
	}
	if(num == 0){
		printf("0");
	}
	printf("\n");
}
