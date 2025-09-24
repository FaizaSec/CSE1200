#ifndef VARIABLE_H
#define VARIABLE_H

// Screen size
int screen_width = 1280;
int screen_height = 720;

int currentLevel = 0; // 0 = none, 1/2/3 = chosen level //for highscore and other methods
bool gameOver = false, gamePaused = false;
bool pKey = false;

// Hover tracking
bool isHovering[5] = { false, false, false, false, false };


//level hovering
bool isHoveringLevel[3] = { false, false, false };

//******************************************
//new code for lock level 
bool levelUnlocked[3] = { true, true, true };



// Sound
const char* clickSound = "sounds/click.wav";

// goalpost image variable
int goalpostImage;
int footballImage;


//character variables
int character[6], characterIndex = 0;
int characterX = 100, characterY = 100;
int walkSpeed = 3;
char filename[50];
int moving = 0;

//ball variables
double ball_x = 200, ball_y = 10, ball_width = 60, ball_height = 60;
double ball_vx = 0, ball_vy = 0;
bool ball_moving = false, ballAttached = true, ball_saved = false;
int ball_speed = 1;

//level3 goalpost
int Goalpost3, gp3X = 1000, gp3Y = 150;





#endif