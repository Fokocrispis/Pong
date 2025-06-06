#pragma once

#ifndef PONG_H
#define PONG_H

#include <stdint.h>
#include <stdbool.h> 

// Gameloop definitions
#define TIMER 50000000
extern bool pause;

// Screen size definitions
#define WIDTH 30
#define HEIGHT 10
#define PLAYER_START 3

// Object constants
#define BALL 'O'
#define PLAYER 'I'
#define WALL '-'
#define CORNER '+'

// Position and speed vector
struct vector {
	int x;
	int y;
};

struct player {
	int y;
	int x;
	int length;
	int speed;
};

// Game control functions
void initGame(void);
void resetGame(void);
void pauseGame(void);
void resumeGame(void);
void updateGame(void);

// Player functions
void player1Input(vector);
void player2Input(vector);


#endif
