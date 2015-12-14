#include <stdio.h>
#include <string.h>

int is_open_frame(int input);
int no_error(int prev, int input, int j, int i); 
int extra_round(int frame);
int is_spare(int first, int second);
int is_strike(int input);
int print_board();
// Initializing the 2D array for manipulating data 
int board[10][4] = {
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},							  
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1},
							  {-1, -1, -1, -1}

						 };
// Initializing ROW & COL for data entry
int NUM_ROWS = 10;
int NUM_COLS = 2;
int current_score = 0;

int main() {

	int input;
	int counter;	
	int prev = 0;
	int add_two_rounds = 2;
	int add_one_round  = 1;
	int spare          = 1;
	int strike 		   = 2;
    int boolean_spare  = 0;
    int boolean_strike = 0;
    int checker        = 0;
  	
  	printf("Welcome to BOWLING 101. Bowling Score Calculator.\n");
  	printf("Enter the # of knocked pins below: (don't use non-integer characters!)\n");
	for (int i = 0; i < NUM_ROWS; i ++) {
		for (int j = 0; j < NUM_COLS; j ++) {
			
			printf("> ");
			scanf("%d", &input);
			if (no_error(prev, input, j, i)) {

				if (j == 0) {
					board[i][j] = input;
				}
				
				// If a spare was bowled in the previous frame 
				if (boolean_spare && j != 1) {
					current_score 	   += input + 10;
					board[i - 1][3] 	= current_score;
					boolean_spare       = 0;
				}
				// If a strike was bowled in the previous frame
				if (boolean_strike > 1 || (j == 1 && boolean_strike > 0)) {
					current_score += input + prev + 10;
					board[i - boolean_strike][3] = current_score;
					boolean_strike --;
				}

				// Trake when  strike is made
				if (is_strike(input)) {	
					if (i != 9) {
						boolean_strike += 1;
						board[i][0] = 10;
						prev = input;
						print_board();
						break;
					} else {
						if (j == 0) {	
							NUM_COLS ++;
						}
					}
				}	

				// Ignore every bowl in R1 that is not a strike, but keep track of it in 'prev'
				checker = ((prev == 10 && input == 0)) ? 0 : 1;
				if (j == 1) {
					if (is_spare(prev, input) && checker) {
						board[i][1]   = -2;
						boolean_spare = 1;
						if (i == 9) {
							NUM_COLS ++;
							current_score += prev + input;
							boolean_spare = 0;
						}
					} else {
						current_score += prev + input;
						board[i][j]    = input;
						board[i][3]    = current_score;
					}
				}
				// Catch the last R3 accounted bowls for frame '10'
				if (j == 2) {
					current_score += input;
					board[i][j]    = input;
					board[i][3]    = current_score;
				}

				// Print the board each bowl turn
				print_board();
				checker = 0;
				prev = input;
			} else {

				// Tell user when trying to enter invalid value. 
				printf("Incorrect Input, try again.\n");
				j--;
			}
		}		
	}

}


				/*  HELPER FUNCTIONS BELOW */


int is_open_frame(int input) {
	return (input != 10) ? 1 : 0;
}

int no_error(int prev, int input, int j, int i) {
	int valid = 1;
	if (j == 1 && i != 9) {
		if ((prev + input) > 10) {
			valid = 0;
		} else {
			valid = 1;
		}
	}
	return (valid && (input <= 10 && input >= 0)) ? 1 : 0;
}

int extra_round(int frame) {
	return (frame == 10) ? 1 : 0;
}


int is_spare(int first, int second) {
	return ((first + second) == 10) ? 1 : 0;
}


int is_strike(int input) {
	return (input == 10) ? 1 : 0;
}
/* This board is manipulated on 4 known numbers :
	-1 = Empty space
	-2 = Slash mark for spares
	 X = A strike
	if neither above, it is a given score for each turn. 
*/
int print_board() {
	printf("\n");
	for (int i = 0; i < 11; i ++) {

		for (int j = 0; j < 4; j++) {
			printf("+-----");
			if (j == 3) {
				printf("+-----+");
			}
		}

// ---------------  open: represent digits in string format ------------ 

		printf("\n");
		char str[15]= "";
		if (board[i - 1][0] == -2) {
			strcpy(str, "/");
		} else if (board[i - 1][0] == 10) {
			strcpy(str, "X");
		} else if (board[i - 1][0] != -1) { 
			sprintf(str, "%d", board[i - 1][0]);
		}

		char str1[15]= "";
		if (board[i - 1][1] == -2) {
			strcpy(str1, "/");
		} else if (board[i - 1][1] == 10) {
			strcpy(str1, "X");
		} else if (board[i - 1][1] != -1) { 
			sprintf(str1, "%d", board[i - 1][1]);
		}

		char str2[15]= "";
		if (board[i - 1][2] == -2) {
			strcpy(str2, "/");
		} else if (board[i - 1][2] == 10) {
			strcpy(str2, "X");
		} else if (board[i - 1][2] != -1) { 
			sprintf(str2, "%d", board[i - 1][2]);
		}

		char str3[15]= "";
		if (board[i - 1][3] == -2) {
			strcpy(str3, "/");
		} else if (board[i - 1][3] == 10) {
			strcpy(str3, "X");
		} else if (board[i - 1][3] != -1) {
			sprintf(str3, "%d", board[i - 1][3]);
		}


// ------------------   closed   ---------------------

		if (i == 0) {		
			printf("| FR  | R1  | R2  | R3  |score|\n");
		} else if (board[i - 1][1] == 10) {
			strcpy(str1, "X");
		} else {
			printf("| %3d | %3s | %3s | %3s | %3s |\n", 
				i, str, str1, str2, str3);
		}
	}

	for (int j = 0; j < 4; j++) {
		printf("+-----");
		if (j == 3) {
			printf("+-----+\n\n\n");
		}
	}
	return 0;
}



