#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "Pong.h"


// To do: read keyboard using UART
void gameFunctions() {

	if (_kbhit()) {
		int key = _getch();
		if (key == 'r') resetGame();
		else if (key == 'u') resumeGame();
	}
}



// To do: replace software timer with a hardware timer
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