#include "Pong.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


// To do: replace chars for booleans for easy hex conversion. 
// Game logic can be kept and printing can be done as follows: pass values from char map[][] to boolean bitMap[][]. 
// If char != ' ' then value in bitMap = 1, else = 0; Search for spaces to convert from char to bit representation.
// Each column represents 2 hex numbers that can be directly used on the pendulum.
char map[HEIGHT][WIDTH];

struct vector ballPosition;
struct vector ballSpeed;

struct player player1;
struct player player2;

int x, y;
int i;

bool pause = false;

void initMap() {
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			if (x == ballPosition.x && y == ballPosition.y) {
				map[y][x] = BALL;
			}
			else if (((x==player1.x && (y >= player1.y)&&(y <= player1.y+player1.length-1)) || (x == player2.x && (y >= player2.y) && (y <= player2.y + player2.length - 1)))) {
				map[y][x] = PLAYER;
			}
			else if ((x == 0 && y == 0) || (x == 0 && y == HEIGHT-1) || (x == WIDTH -1 && y == 0) || (x == WIDTH -1 && y == HEIGHT -1)) {
				map[y][x] = CORNER;
			}
			else if (x == 0 || x == WIDTH-1) {
				map[y][x] = ' ';
			}
			else if (y == 0 || y == HEIGHT - 1) {
				map[y][x] = WALL;
			}
			else{
				map[y][x] = ' ';
			}
		}
	}
}

// To do: printing has to be adapted to uC
void printMap(void) {
	int x, y, z = 0;

	// Clean command line in windows
	system("cls");

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			printf("%c", map[y][x]);
		}
		printf("\n");
	}
}

void initGame(void) {
	ballPosition.x = 5;
	ballPosition.y = 5;

	ballSpeed.x = -1;
	ballSpeed.y = 0;

	player1.y = PLAYER_START;
	player1.x = 0;
	player1.speed = 1;
	player1.length = 3;

	player2.y = PLAYER_START;
	player2.x = WIDTH-1;
	player2.speed = -1;
	player2.length = 3;

	initMap();
	printMap();
}

void resetGame(void) {
	initGame();
	pause = false;

}
void pauseGame(void) {
	pause = true;
}
void resumeGame(void) {
	pause = false;
}


// To do: keyboard input to be replaced by joystick output
void checkInput() {
	static int lastKey = 0;

	if (_kbhit()) {
		int key = _getch();
		lastKey = key;

		if (key == 224 || key == 0) {
			key = _getch();

			if (key == 72) player2.speed = -1;      // Up arrow
			else if (key == 80) player2.speed = 1;   // Down arrow
		}
		else if (key == 'w' || key == 'W') player1.speed = -1;
		else if (key == 's' || key == 'S') player1.speed = 1;
		else if (key == 'p') pauseGame();
	}
	else {
		// Stop movement when no key is pressed
		player1.speed = 0;
		player2.speed = 0;
	}
}

void updateGame(void) {
	// Player update
	checkInput();
	if ((player1.y + player1.speed > 0) && (player1.y + player1.speed + player1.length) < HEIGHT) {
		player1.y += player1.speed;
	}
	if ((player2.y + player2.speed > 0) && (player2.y + player2.speed + player2.length) < HEIGHT) {
		player2.y += player2.speed;
	}

	// Ball update - wall collision
	if ((ballPosition.y + ballSpeed.y) >= HEIGHT || (ballPosition.y + ballSpeed.y) < 0) {
		ballSpeed.y = -ballSpeed.y;
	}

	// Player 1 paddle collision
	if (((ballPosition.x + ballSpeed.x) == player1.x) &&
		(ballPosition.y >= player1.y) &&
		(ballPosition.y <= player1.y + player1.length - 1)) {

		ballSpeed.x = -ballSpeed.x;

		// Determine which part of paddle was hit
		int relativeHit = ballPosition.y - player1.y;
		if (relativeHit == 0) {
			ballSpeed.y = -1;      // Top section - ball goes up
		}
		else if (relativeHit == 1) {
			ballSpeed.y = 0;       // Middle section - straight bounce
		}
		else {
			ballSpeed.y = 1;       // Bottom section - ball goes down
		}
	}
	// Player 2 paddle collision
	else if (((ballPosition.x + ballSpeed.x) == player2.x - 1) &&
		(ballPosition.y >= player2.y) &&
		(ballPosition.y <= player2.y + player2.length - 1)) {

		ballSpeed.x = -ballSpeed.x;

		// Determine which part of paddle was hit
		int relativeHit = ballPosition.y - player2.y;
		if (relativeHit == 0) {
			ballSpeed.y = -1;      // Top section - ball goes up
		}
		else if (relativeHit == 1) {
			ballSpeed.y = 0;       // Middle section - straight bounce
		}
		else {
			ballSpeed.y = 1;       // Bottom section - ball goes down
		}
	}
	// Goal detection
	else if (ballPosition.x == 0 || ballPosition.x == WIDTH - 1) {
		pauseGame();
		if (ballPosition.x == 0) printf("Player 1 lost!");
		else printf("Player 2 lost!");
	}

	// Update ball position
	ballPosition.x += ballSpeed.x;
	ballPosition.y += ballSpeed.y;

	initMap();
}