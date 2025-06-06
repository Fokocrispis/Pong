#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "Pong.h"

void gameFunctions() {

	if (_kbhit()) {
		int key = _getch();
		if (key == 'r') resetGame();
		else if (key == 'u') resumeGame();
	}
}

int main(void) {
	initGame();


	while (1) {
		if (!pause) {
			printMap();
			updateGame();
		}
		gameFunctions();
		for (int i = 0; i < TIMER; i++);

	}

	return 0;
}