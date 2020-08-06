#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "Rectangle.h"
#include <deque>
#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.h"
#include "Enemies.h"
#include "playerObj.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class App: public GlutApp {

    
	Rectangle* r;
   	bool right;
	bool left;
	bool up;
	bool down;
	bool paused;
    	bool gameOver;
	bool gameLoop;

	float theta;
	float inc;
	float r1;
	float r2;
	float r3;
    	float missleX;
	float missleY;
	float missleX1;
	float missleY1;
	float missleX2;
	float missleY2;
    	int missleCount;
    
public:

	TexRect* background;
	playerClass* playerChar = new playerClass(0.0, - 0.7, 0.1, 0.1);
	float mx;
	float my;
	int state; 
	int score;
	int var;
	int highscore;
	int spritesKilled = 0;
	char strscore[10];

	App(const char* label, int x, int y, int w, int h);
    
	void draw();
	void keyPress(unsigned char key);
	
	void idle();
	void print(float x, float y, float z, char *string);
	void mouseDown(float x, float y);
	void getScores();
	void saveScore();
	void resetGame(int stateHold);
	~App();

};

#endif
