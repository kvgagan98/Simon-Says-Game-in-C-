/*
	Name: Gagan Kanisetty
	Purpose: User plays simon game it has 5 levels. Each level there is one more colour that the user has to remember and the speed also increases. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <DAQlib.h>

#define GREEN 0 
#define RED 1
#define YELLOW 2
#define BLUE 3

void randomSequence(int clevel, int arr[4]);  /* Generates random sequence of numbers between 0 to 3 */
void level(void); /* Generates Levels */
void userturn(int N, int arr1[4]); /* Enables user to press buttons */
void blink(int number); /* Blinks the colour 3 times if user loses */
int main(void) {
	int userinput;

	if (setupDAQ(6) == 1) {
		level();
	}
	else {
		printf("Error! Please enter 6\n");
	}

	system("PAUSE");
	return 0;
}

void level(void) {
	int currentlevel = 0;
	int randomize[4] = {0,0,0,0};
	int index;

	srand((unsigned)time(NULL));
	while (continueSuperLoop() == TRUE) {
		if (currentlevel < 5) {
			currentlevel++;
			for (index = 0; index < currentlevel; index++) {
				randomize[index] = rand() % 4;
			}
			randomSequence(currentlevel, randomize);
		}
		else if (currentlevel == 5) {
			printf("You Win!\n");
			system("PAUSE");
			return 0;
		}
	}
}

void randomSequence(int clevel, int arr[4]) {
	int i;
	int timesleep;

	timesleep = 1000 / clevel;
	Sleep(timesleep);
	for (i = 0; i < clevel; i++) {
		digitalWrite(arr[i], 1);
		Sleep(timesleep);
		digitalWrite(arr[i], 0);
		Sleep(timesleep);
	}
	userturn(clevel, arr);
}

void userturn(int N, int arr1[4]) {
	for (int j = 0; j < N; j++) {
		int green = digitalRead(GREEN);
		int red = digitalRead(RED);
		int yellow = digitalRead(YELLOW);
		int blue = digitalRead(BLUE);

		while (green == 0 && red == 0 && yellow == 0 && blue == 0) {
			green = digitalRead(GREEN);
			red = digitalRead(RED);
			yellow = digitalRead(YELLOW);
			blue = digitalRead(BLUE);

			if (green == 1) {
				if (arr1[j] == GREEN) {
					digitalWrite(GREEN, 1);		/* Switch it on */
					Sleep(200);					/* Not for very long */
					digitalWrite(GREEN, 0);
				}
				else {
					blink(GREEN);
				}
			}
			else if (red == 1) {
				if (arr1[j] == RED) {
					digitalWrite(RED, 1);		/* Switch it on */
					Sleep(200);					/* Not for very long */
					digitalWrite(RED, 0);
				}
				else {
					blink(RED);
				}
			}
			else if (yellow == 1) {
				if (arr1[j] == YELLOW) {
					digitalWrite(YELLOW, 1);
					Sleep(200);
					digitalWrite(YELLOW, 0);
				}
				else {
					blink(YELLOW);
				}
			}
			else if (blue == 1) {
				if (arr1[j] == BLUE) {
					digitalWrite(BLUE, 1);		/* Switch it on */
					Sleep(200);					/* Not for very long */
					digitalWrite(BLUE, 0);
				}
				else {
					blink(BLUE);
				}
			}
		}
	}
}

void blink(int number) {
	digitalWrite(number, 1);
	Sleep(250);
	digitalWrite(number, 0);
	Sleep(250);
	digitalWrite(number, 1);
	Sleep(250);
	digitalWrite(number, 0);
	Sleep(250);
	digitalWrite(number, 1);
	Sleep(250);
	digitalWrite(number, 0);
	Sleep(250);
	printf("YOU LOOSE!\n");
	system("PAUSE");
	return 0;
}