#include "iGraphics.h"
#include "LoadNmenu.hpp"
#include "GoalPost.hpp"
#include "Variable.hpp"
#include "Level2Goalpost.hpp"
#include "jerseychoose.hpp"
#include "puzzle.hpp"
#include "Character.hpp"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//int x = 0;
//int y = 0;


void iDraw()
{
	iClear();
	
	if (currentState == SPLASH) {
		iShowImage(0, 0, 1280, 720, posterImage);

	}
	else if (currentState == MENU) {
		drawMenu();
	}
	else if (currentState == EXIT) {
		exit(0);
	}
	else if (currentState == LEVEL_SELECT) {
		drawLevelSelect();
		//drawText();

	}
	else if (currentState == PLAY) {
		drawPage(currentState);      //to just show the play then level
		drawText();      //not to show this on every page just in level1,level2&level3 seperately
	}
	else {
		drawPage(currentState);
	}


}

void iMouseMove(int mx, int my)
{
	
}

//detect hover
void iPassiveMouseMove(int mx, int my)
{
	if (currentState == MENU){
		for (int i = 0; i < 5; i++) {
			int y = by_start - i * gap;
			isHovering[i] = (mx >= bx && mx <= bx + buttonW && my >= y && my <= y + buttonH);
		}
	}
	else if (currentState == LEVEL_SELECT) {
		for (int i = 0; i < 3; i++) {
			int y = lvlByStart - i * lvlGap;
			isHoveringLevel[i] = (mx >= lvlBx && mx <= lvlBx + lvlButtonW && my >= y && my <= y + lvlButtonH);
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (currentState == MENU) {

			for (int i = 0; i < 5; i++) {

				int y = by_start - i * gap;

				if (mx >= bx && mx <= bx + buttonW && my >= y && my <= y + buttonH) {
					PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);
					if (i == 0) currentState = LEVEL_SELECT; // Play → Level Select 
					if (i == 1) currentState = INSTRUCTIONS;
					if (i == 2) currentState = ABOUT;
					if (i == 3) currentState = SETTINGS;
					if (i == 4) currentState = EXIT;
					break;
				}
			}
		}

		else if (currentState == LEVEL_SELECT) {
			// Click level 1/2/3
			for (int i = 0; i < 3; i++) {

				int y = lvlByStart - i * lvlGap;

				if (mx >= lvlBx && mx <= lvlBx + lvlButtonW && my >= y && my <= y + lvlButtonH) {

					//******************************************
					//new code for lock level 
					if (levelUnlocked[i]) {
						PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);

						//currentLevel = i + 1;

						//currentState = PLAY; // start actual game

						//*******************************************
						if (i == 0) { // Level 1
							currentLevel = 1;
							currentState = PLAY;
						}
						else if (i == 1) { // Level 2
							currentLevel = 2;
							currentState = JERSEY_SELECT; // show jersey page
						}
						else if (i == 2) { // Level 2
							currentLevel = 3;

							//--------------------------------------------------
							currentState = PUZZLE; // show jersey page
							initPuzzle();   // reset/prepare puzzle now
							//---------------------------------------------

						}
						//**********************************************************

						//currentState = PLAY; // start actual game

						gamePaused = false;

						gameOver = false;


						if (currentLevel == 1){ gameTime[currentLevel - 1] = 60; }//shova
						if (currentLevel == 2){ gameTime[currentLevel - 1] = 30; }
						if (currentLevel == 3){ gameTime[currentLevel - 1] = 90; }
						score[currentLevel - 1] = 0;
						break;
					}
					//******************************************

				}
			}
			// Back arrow
			if (mx >= 30 && mx <= 90 && my >= 630 && my <= 690) {
				PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);
				currentState = MENU;
			}
		}

		else if (currentState == PLAY) {
			// Back arrow from Play -> Level Select
			if (mx >= 30 && mx <= 90 && my >= 630 && my <= 690) {
				gamePaused = true; // Show "Pause / Quit" warning
				currentState = LEVEL_SELECT;
				restartLevel();//yayaya restart level shova
				//------------------------------------------------------------
				//reset goalpost ??
				ResetRealGoalpost();

				//puzzle restart
				//resetPuzzle();

			}
		}

		//**********************************************************************
		//jersey select page
		else if (currentState == JERSEY_SELECT) {
			// Blue jersey
			if (mx >= 300 && mx <= 500 && my >= 200 && my <= 400) {
				selectedJersey = 1;
				currentCharacterImages = characterImagesBlue;
				currentState = PLAY;
				currentLevel = 2; // Start level 2
			}
			// Pink jersey
			else if (mx >= 800 && mx <= 1000 && my >= 200 && my <= 400) {
				selectedJersey = 2;
				currentCharacterImages = characterImagesPink;
				currentState = PLAY;
				currentLevel = 2; // Start level 2
			}

			// Back arrow
			if (mx >= 30 && mx <= 90 && my >= 630 && my <= 690) {
				PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);
				currentState = LEVEL_SELECT;
			}
		}

		//--------------------------------------------------------------
		//puzzle page
		// inside iMouse(), where you handle LEFT button & state
		else if (currentState == PUZZLE) {

			currentState = PUZZLE;
			if (mx >= 30 && mx <= 90 && my >= 630 && my <= 690) {
				PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);
				currentState = LEVEL_SELECT; // go back to level select
			}
			else {
				// forward the click to puzzle logic (this checks which tile was clicked)
				puzzle_mousemove(mx, my);
			}
		}
		//----------------------------------------------------------------------------------

		else {
			if (mx >= 30 && mx <= 90 && my >= 630 && my <= 690) {
				PlaySound(clickSound, NULL, SND_FILENAME | SND_ASYNC);
				currentState = MENU;
			}
		}





		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (currentLevel == 1 || currentLevel == 2){
			ballDetachment(mx, my);//ball will seperate from character after mouse click
		}

		//-------------------------------------------------
		//puzzle page er jonno dont't know abt this
		/*if (currentLevel == 3){
		puzzle_mousemove(mx, my);
		}*/

		else if (currentLevel == 3 && currentState == PLAY) {
			// if you want right-click to also work in level3 play, handle here
			puzzle_mousemove(mx, my);
			ballDetachment(mx, my);
		}
	}
}

// Auto move to menu after 3 seconds (3000 ms)
void goToMenu() {
	if (currentState == SPLASH) {
		currentState = MENU;
	}
}

void moveGoalpost() {
	if (gameOver || gamePaused || currentState != PLAY) return; // Stop when game is over new try
	goal.moveGp1();//move and reset
}
void moveKeeper1() {
	if (gameOver || gamePaused || currentState != PLAY) return; // Stop when game is over new try
	gk.moveKeeper();//move and reset
}



// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate()
{
	//shova
	if (currentState != PLAY) return;
	// Handle pause/resume/quit keys
	if (isKeyPressed('p') || isSpecialKeyPressed(GLUT_KEY_INSERT)){
		if (!pKey) {
			//gamePaused= true;
			gamePaused = !gamePaused; // Pause+resume


			pKey = true;
			return;
		}
		else {
			pKey = false;  // reset when key is released
		}
	}
	else if (gamePaused) {
		if (isKeyPressed('r') || isKeyPressed('R')){
			printf("R pressed!\n");
			restartLevel();   // restart instead of just unpausing
			ResetRealGoalpost();

			// ADD THIS
			//resetPuzzle(); // back to question 1

		}
		if (isKeyPressed('Q') || isKeyPressed('q')) {
			printf("Q pressed!\n");
			// ADD THIS
			//resetPuzzle(); // back to question 1

			quitToLevelSelect(); // quit properly
			ResetRealGoalpost();


		}
		return; // stay here while paused
	}
	else if (gameOver){

		//new
		if (isKeyPressed('r') || isKeyPressed('R')){
			printf("R pressed!\n");


			// ADD THIS
			//resetPuzzle(); // back to question 1

			restartLevel();   // restart instead of just unpausing

		}
		if (isKeyPressed('Q') || isKeyPressed('q')) {
			printf("Q pressed!\n");


			// ADD THIS
			//resetPuzzle(); // back to question 1

			quitToLevelSelect(); // quit properly
		}
		return; // stay here while paused

	}


	static int frameCounter = 0;
	int moving = 0;




	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
	{
		if (currentLevel == 1 || currentLevel == 2 || currentLevel == 3){
			if ((characterY + 100) < 400 || (ball_y + ball_height) < 400){
				characterY += walkSpeed;
				moving = 1;
				ball_y += ball_speed;
			}
		}
	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{
		if (currentLevel == 1 || currentLevel == 2 || currentLevel == 3){
			if (characterX > 50 || ball_x > 50){
				characterX -= walkSpeed;
				moving = 1;
				ball_x -= ball_speed;
			}
		}
	}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
	{
		if (currentLevel == 1 || currentLevel == 2 || currentLevel == 3){
			if (characterY > 50 || ball_y > 50){
				characterY -= walkSpeed;
				moving = 1;
				ball_y -= ball_speed;
			}
		}
	}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{
		if (currentLevel == 1 || currentLevel == 2 || currentLevel == 3){
			if ((characterX + 100) < 640 || (ball_x + ball_width) < 640){
				characterX += walkSpeed;
				moving = 1;
				ball_x += ball_speed;
			}
		}
	}

	/*if (isKeyPressed(' ')) {
		// Playing the audio once
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}*/

	if (currentLevel == 1 || currentLevel == 2 || currentLevel == 3){
		// Ball follows feet if attached
		if (ballAttached) {
			ball_x = characterX + 60;
			ball_y = characterY + 10;
		}
		// Reset only if character hits top, bottom, or left
		if (characterX < 0 || characterY < 0 || characterY + 100 > 720) {
			resetCharacterPosition();
		}
		// Clamp right boundary (no reset)
		if (characterX + 100 > 550) {
			characterX = 550 - 100;
		}
		//image movement function
		if (moving) {
			frameCounter++;
			if (frameCounter >= 6) {
				characterIndex = (characterIndex + 1) % 6;
				frameCounter = 0;
			}
		}
		else {
			characterIndex = 0; // idle frame when not moving
		}
		move_ball();// handle collisions & goal for level 1 add level 2 in this method
		// Floating GOAL text
		goalText();//new method

		//******************************************
		//new code for lock level 

		// Unlock next level if score conditions met
		if (currentLevel == 1 && score[0] >= 1) {
			levelUnlocked[1] = true; // Unlock Level 2
		}
		if (currentLevel == 2 && score[1] >= 1) {
			levelUnlocked[2] = true; // Unlock Level 3
		}

		//******************************************

	}

	//******************************************
	//new code for lock level 

	if (currentLevel == 3){
		if (showFeedback) {
			feedbackTimer--;
			if (feedbackTimer <= 0) {
				showFeedback = false;
			}
		}
	}


}


int main()
{
	// Opening/Loading the audio files
	mciSendString("open \"Audios//bg.mp3\" alias bgsong", NULL, 0, NULL);//adeeba
	mciSendString("open \"Audios//levelComplete.mp3\" alias ggsong", NULL, 0, NULL);

	//mciSendString("open \"Audios//background.mp3\" alias bgsong", NULL, 0, NULL);
	//mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);

	// Playing the background audio on repeat
	mciSendString("play bgsong repeat", NULL, 0, NULL);

	srand(time(0)); // Random seed
	goal.init(); // Set initial values
	gk.init();


	// If the use of an audio is finished, close it to free memory
	// mciSendString("close bgsong", NULL, 0, NULL);
	// mciSendString("close ggsong", NULL, 0, NULL);

	iInitialize(screen_width, screen_height, "SAF:BETWEEN YOU AND THE NET");


	loadMenuAssets();
	loadKeeper();
	//character image load
	loadCharacterImages();

	// Goal Sound
	mciSendString("open \"Audios/goal.mp3\" alias goalsound", NULL, 0, NULL);//till

	//timerIdDraw = iSetTimer(16, iDraw); // screen refresh-60s refresh
	iSetTimer(3000, goToMenu); // Splash timer 3 sec splash
	iSetTimer(50, fixedUpdate);
	iSetTimer(20, move_ball);
	iSetTimer(30, moveGoalpost); // goalpost
	iSetTimer(30, moveKeeper1);
	iSetTimer(1000, updateTime);// timer - 1 sec timer//me merge

	//============================================================================================
	iSetTimer(100, updateConfetti);//new
	loadJerseyImages();//load blue pink sprite sheet
	initPuzzle();

	iStart();
	return 0;
}