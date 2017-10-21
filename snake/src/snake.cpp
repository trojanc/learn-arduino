#include "snake.h"

/**
 * Reference to the screen
 */
PDQ_ILI9340 tft;

/**
 * Size of each grid block
 */
const int gs=GRID_SIZE;

/**
 * Key state determining the direction we are moving in
 */
volatile int keyState = 0;

/**
 * Timestamp the last time a key was pressed, used for debouncing
 */
volatile unsigned long previousKey = 0;

/**
 * Timestampe the game was last updated
 */
unsigned long previousGame = 0;

	// Player position
int px=0, py=0,
	// Apple X and Y
	ax=0, ay=0,
	// Velocity X and Y
	xv=1, yv=0;

/**
 * Array of trail coordinates
 */
tailPosition trail[TAIL_POSITIONS];

/**
 * Length of the tail
 */
int tail = STARTING_SIZE;

/**
 * Creates a new apple
 */
void newApple(){
	ax=round(random(0, TILE_COUNTX));
	ay=round(random(0, TILE_COUNTY));
}


/**
 * Restarts the game
 * @param died Flag if the player bit its tail
 */
void restartGame(bool died = false){
	if(died){
		tft.fillScreen(ILI9340_RED);
		tft.setTextColor(ILI9340_BLUE);
		tft.setTextSize(4);
		tft.setCursor(0,0);
		tft.println();
		tft.println();
		tft.println();
		tft.println();
		tft.println("GAME  OVER");
		tft.println();
		tft.setTextColor(COLOR_SCORE);
		tft.setTextSize(3);
		tft.print("     ");
		tft.print(tail-STARTING_SIZE);
		delay(2000);
	}
	tft.fillScreen(COLOR_BACKGROUND);
	px=round(random(0, TILE_COUNTX));
	py=round(random(0, TILE_COUNTY));
	tail = STARTING_SIZE;
	for(int i = 0 ; i < tail ; i++){
		trail[i] = {px,py};
	}
	newApple();
}

/**
 * Interupt invokes this when a key is pressed
 */
void readKey(){
	unsigned long now = millis();
	if(now - previousKey > 150){
		previousKey = now;
		keyState++;
		if(keyState > 3){
			keyState = 0;
		}
		switch(keyState) {
		case 0:
			xv=-1;yv=0;
			break;
		case 1:
			xv=0;yv=1;
			break;
		case 2:
			xv=1;yv=0;

			break;
		case 3:
			xv=0;yv=-1;
			break;
		}
	}
}

/**
 * Execute the game
 */
void game(void) {
	px+=xv;
	py+=yv;
	if(px<0) {
		px = TILE_COUNTX - 1;
	}
	if(px>TILE_COUNTX-1) {
		px= 0;
	}
	if(py<0) {
		py = TILE_COUNTY-1;
	}
	if(py > TILE_COUNTY-1) {
		py= 0;
	}
	for(int i = 0; i < tail; i++) {
		// We only have to redraw the head and the tail of the snake
		if(i == 0 || i == tail-1){
			tft.fillRect(trail[i].x * gs,trail[i].y*gs, gs-1, gs-1, COLOR_SNAKE);
		}

		// If you bit your tail
		if(trail[i].x == px && trail[i].y == py) {
			restartGame(true);
			return;
		}
	}

	// Fill over the previous tail location
	tft.fillRect(trail[0].x * gs,trail[0].y*gs, gs-1, gs-1, COLOR_BACKGROUND);

	// Shift the body up one position
	memcpy(&trail[0], &trail[1], (tail-1)*sizeof(*trail));
	trail[tail-1] = {px,py};

	// Check if we caught the apple
	if(ax==px && ay==py) {
		tail++;
		trail[tail-1] = {px,py};
		newApple();
	}

	// Draw the location of the apple
	tft.fillRect(ax*gs,ay*gs,gs-1,gs-1, COLOR_APPLE);
}


void setup() {
	Serial.begin(115200);
	while (!Serial);
#if defined(ILI9340_RST_PIN)	// reset like Adafruit does
	FastPin<ILI9340_RST_PIN>::setOutput();
	FastPin<ILI9340_RST_PIN>::hi();
	FastPin<ILI9340_RST_PIN>::lo();
	delay(1);
	FastPin<ILI9340_RST_PIN>::hi();
#endif
	// Init random for player and apple placement
	randomSeed(analogRead(A0));
	pinMode(2, INPUT);

	attachInterrupt(digitalPinToInterrupt(2), readKey, RISING);

	tft.begin();

// Rotate the display if you need to
// tft.setRotation(1);
	restartGame();
}

void loop(){
	unsigned long now = millis();

	if(now - previousGame > 1000/10){
		game();
		previousGame = now;
	}
}
