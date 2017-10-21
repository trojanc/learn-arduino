#ifndef SRC_SNAKE_H_
#define SRC_SNAKE_H_

#include <Arduino.h>
#include "SPI.h"
#include "PDQ_ILI9340_config.h"
#include "PDQ_GFX.h"
#include "PDQ_ILI9340.h"

#define SCKL 13
#define MISO 12
#define MOSI 11
#define CS 10
#define DC 9
#define RST 8

/**
 * Struct defining the coordinates for a tail piece.
 */
struct tailPosition {
	int x;
	int y;
};


/**
 * Background Color
 */
#define COLOR_BACKGROUND 0x5D1C

/**
 * Snake color
  */
#define COLOR_SNAKE 0x87E0

/**
 * Score color
 */
#define COLOR_SCORE 0x000F

/**
 * Apple color
 */
#define COLOR_APPLE ILI9340_RED

// Scope these if changing orientation
//#define SCREEN_Y 240
//#define SCREEN_X 320

#define SCREEN_X 240
#define SCREEN_Y 320

/**
 * Number of pixels for a grid item
 */
#define GRID_SIZE 10

/**
 * Number of tiles on the x-axis
 */
#define TILE_COUNTX (SCREEN_X/GRID_SIZE)

/**
 * Number of tiles on the y-axis
 */
#define TILE_COUNTY (SCREEN_Y/GRID_SIZE)

/**
 * Number of tail items we can have before filling the entire screen
 */
#define TAIL_POSITIONS (TILE_COUNTX*TILE_COUNTY)

/**
 * Size of the tail when starting a new game
 */
#define STARTING_SIZE 5

#endif /* SRC_SNAKE_H_ */
