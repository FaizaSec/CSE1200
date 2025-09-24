#ifndef LOADNMENU_H
#define LOADNMENU_H

#include "Character.hpp"

// Menu/Level images
int posterImage;
int bg_menu, bg_play, bg_instr, bg_about, bg_settings;
int btn1, btn2, btn3, btn4, btn5;
int btn1_hover, btn2_hover, btn3_hover, btn4_hover, btn5_hover, btn_continue;
int back_arrow;
int bg_level1, bg_level2, bg_level3;

// Button positions
const int bx = 520;
const int by_start = 500;
const int buttonW = 240;
const int buttonH = 60;
const int gap = 70;

//level er button position
//******************************************
//new code for lock level 
int lvl2_locked, lvl3_locked;

bool isLevel2Unlocked = false;
bool isLevel3Unlocked = false;
//******************************************

//level er button position//changed it from my level 3 projrct
const int lvlBx = 520;
const int lvlByStart = 400;
const int lvlButtonW = 260;
const int lvlButtonH = 80;
const int lvlGap = 60;

// Level buttons
int lvl1, lvl2, lvl3;
int lvl1_hover, lvl2_hover, lvl3_hover;



void loadMenuAssets() {
	posterImage = iLoadImage("image/poster.png");
	if (posterImage == -1){
		printf("poster.png failed to load!\n");
	}
	bg_menu = iLoadImage("image/picture1.png");
	bg_play = iLoadImage("image/play_bg.png");
	bg_instr = iLoadImage("image/instructions_bg.png");
	bg_about = iLoadImage("image/about_bg.png");
	bg_settings = iLoadImage("image/settings_bg.png");

	btn1 = iLoadImage("image/button1.png"); // Play
	btn2 = iLoadImage("image/button2.png"); // Instructions
	btn3 = iLoadImage("image/button3.png"); // About
	btn4 = iLoadImage("image/button4.png"); // Settings
	btn5 = iLoadImage("image/button5.png"); // Exit
	//Hover image
	btn1_hover = iLoadImage("image/button1_hover.png");
	btn2_hover = iLoadImage("image/button2_hover.png");
	btn3_hover = iLoadImage("image/button3_hover.png");
	btn4_hover = iLoadImage("image/button4_hover.png");
	btn5_hover = iLoadImage("image/button5_hover.png");
	btn_continue = iLoadImage("image/button_continue.png");



	lvl1 = iLoadImage("image/level1.png");
	lvl2 = iLoadImage("image/level2.png");
	lvl3 = iLoadImage("image/level3.png");
	lvl1_hover = iLoadImage("image/level1_hover.png");
	lvl2_hover = iLoadImage("image/level2_hover.png");
	lvl3_hover = iLoadImage("image/level3_hover.png");

	//******************************************
	//new code for lock level 
	lvl2_locked = iLoadImage("image/level2_locked.png");
	lvl3_locked = iLoadImage("image/level3_locked.png");
	//******************************************


	// Level backgrounds
	bg_level1 = iLoadImage("image/background1.png");
	bg_level2 = iLoadImage("image/background2.png");
	bg_level3 = iLoadImage("image/puzzle_bg.png");

	back_arrow = iLoadImage("image/back_arrow.png");
}//can't be in any header file,for loop? 
// Load all 5 character images from images folder
void loadCharacterImages() {

	for (int i = 0; i < 6; i++) {
		sprintf_s(filename, "image/walk_%d.png", i + 1);
		character[i] = iLoadImage(filename);
		//debug
		if (character[i] == -1)
			printf("Failed to load: %s\n", filename);
		else
			printf("Loaded: %s = %d\n", filename, character[i]);

	}
	//ball image load 
	footballImage = iLoadImage("image/football1.png");
	//goalpost image load
	goalpostImage = iLoadImage("image/goalpost1.png");
	//-------------------------------------------------
	//goalpost image load for level 2 
	LoadGoalpost();

}
void loadKeeper(){
	gk.image[0] = iLoadImage("image/keeper1.png");
	gk.image[1] = iLoadImage("image/keeper2.png");
	Goalpost3 = iLoadImage("image/real_gp1.png");
}
void drawKeeper() {
	iShowImage(gk.keeperX, gk.keeperY, keeper_width, keeper_height, gk.image[0]);
	iShowImage(gk.keeperX, gk.keeperY, keeper_width, keeper_height, gk.image[1]);

}
void drawText(){
	// Score
	char scoreText[20]; sprintf_s(scoreText, "Score: %d", score[currentLevel - 1]);
	iSetColor(255, 255, 0); iText(20, 700, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	// Timer
	char timerText[20]; sprintf_s(timerText, "Time: %02d", gameTime[currentLevel - 1]);
	iText(200, 700, timerText, GLUT_BITMAP_TIMES_ROMAN_24);

	if (showGoalText){ iSetColor(255, 215, 0); iText(ball_x, goalTextY, "GOAL!", GLUT_BITMAP_TIMES_ROMAN_24); }

	if (gameOver){
		iSetColor(255, 0, 0); iText(500, 400, "TIME'S UP!", GLUT_BITMAP_TIMES_ROMAN_24);
		char finalScore[30]; sprintf_s(finalScore, "Your Score: %d", score[currentLevel - 1]);
		iSetColor(255, 255, 255); iText(500, 360, finalScore, GLUT_BITMAP_TIMES_ROMAN_24);

		iText(500, 330, "Press R to Restart", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500, 310, "Press Q to Quit", GLUT_BITMAP_TIMES_ROMAN_24);

	}
	else if (gamePaused){
		iSetColor(255, 255, 0); iText(500, 380, "GAME PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500, 350, "Press R to Restart Level", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500, 330, "Press Q to Quit to Level Select", GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
// Draw menu
void drawMenu() {
	iShowImage(0, 0, 1280, 720, bg_menu);

	iShowImage(bx, by_start, buttonW, buttonH, isHovering[0] ? btn1_hover : btn1); // Play
	iShowImage(bx, by_start - gap, buttonW, buttonH, isHovering[1] ? btn2_hover : btn2);// Instructions
	iShowImage(bx, by_start - 2 * gap, buttonW, buttonH, isHovering[2] ? btn3_hover : btn3); // About
	iShowImage(bx, by_start - 3 * gap, buttonW, buttonH, isHovering[3] ? btn4_hover : btn4);//Settings
	iShowImage(bx, by_start - 4 * gap, buttonW, buttonH, isHovering[4] ? btn5_hover : btn5);// Exit
}//for loop?
void drawBackArrow() {
	iShowImage(30, 630, 60, 60, back_arrow);
}


// Draw level select screen
void drawLevelSelect() {
	iShowImage(0, 0, 1280, 720, bg_play);

	int lvlImages[3];
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			lvlImages[i] = isHoveringLevel[i] ? lvl1_hover : lvl1;
		}
		else if (i == 1) {
			if (!levelUnlocked[1])
				lvlImages[i] = lvl2_locked;
			else
				lvlImages[i] = isHoveringLevel[i] ? lvl2_hover : lvl2;
		}
		else if (i == 2) {
			if (!levelUnlocked[2])
				lvlImages[i] = lvl3_locked;
			else
				lvlImages[i] = isHoveringLevel[i] ? lvl3_hover : lvl3;
		}
		iShowImage(lvlBx, lvlByStart - i * lvlGap * 1.5, lvlButtonW, lvlButtonH, lvlImages[i]);
	}
	//******************************************



	drawBackArrow();
}
// Draw based on state
void drawPage(GameState state) {
	switch (state) {
	case PLAY:
		if (currentLevel == 1) {

			iShowImage(0, 0, 1280, 720, bg_level1);
			// Draw the current image of the character
			iShowImage(characterX, characterY, 100, 100, character[characterIndex]);
			//show ball image
			iShowImage(ball_x, ball_y, ball_width, ball_height, footballImage);
			// loading a goalpost image
			iShowImage(goal.goalpost_x, goal.goalpost_y, goalpost_width, goalpost_height, goalpostImage);

			if (showConfetti) {//new
				showingConfetti();
			}



		}
		else if (currentLevel == 2){
			iShowImage(0, 0, 1280, 720, bg_level2);
			//------------------------------------------------------------------------------
			//show level2 image goalpost
			ShowGoalpostLevel2();

			// Draw the current image of the character
			//iShowImage(characterX, characterY, 100, 100, character[characterIndex]);

			//new*****************************************
			//new character sprite
			if (currentCharacterImages != nullptr) {
				iShowImage(characterX, characterY, 100, 100, currentCharacterImages[characterIndex]);
			}
			//show ball image
			iShowImage(ball_x, ball_y, ball_width, ball_height, footballImage);
			//========================================================================================
			if (showConfetti) {//new
				showingConfetti();
			}
			//===========================================================================================



		}
		else if (currentLevel == 3){

			iShowImage(0, 0, 1280, 720, bg_level2);
			// Draw the current image of the character
			iShowImage(characterX, characterY, 100, 100, character[characterIndex]);

			// loading a goalpost image
			iShowImage(gp3X, gp3Y, goalpost_width, goalpost_height, Goalpost3);
			// draw keeper
			drawKeeper();
			//show ball image
			iShowImage(ball_x, ball_y, ball_width, ball_height, footballImage);
			//======================================================================================
			if (showConfetti) {//new
				showingConfetti();
			}

		}

		break;

	case INSTRUCTIONS:
		iShowImage(0, 0, 1280, 720, bg_instr);

		//adeeba code

		iSetColor(255, 255, 255); // White text

		iSetColor(200, 200, 200); // Light gray for instructions
		iText(100, 480, "1. To start playing the game, enter level and select Level 1", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100, 430, "2. Win in Level 1 will take you to Level 2, and a win in Level 2 will lead you to the ultimate and final Level 3", GLUT_BITMAP_TIMES_ROMAN_24);
		//iText(120, 400, "   will lead you to the ultimate and final Level 3", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100, 400, "3. To play you have to DOUBLE CLICK to goal", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(100, 350, "4. Character moves using WASD keys or Arrow keys", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 255, 0);
		iText(250, 200, "Tap BACK to go to the game", GLUT_BITMAP_TIMES_ROMAN_24);
		//=======================================================adeeba
		break;


	case ABOUT:
		iShowImage(0, 0, 1280, 720, bg_about);
		// Content
		iSetColor(255, 255, 255); // white
		iText(100, 450, "Creators:", GLUT_BITMAP_HELVETICA_18);

		iText(100, 400, "Adeeba Islam", GLUT_BITMAP_HELVETICA_18);
		iText(100, 350, "Shanjida Islam Shova", GLUT_BITMAP_HELVETICA_18);
		iText(100, 300, "Sirazam Munira Faiza", GLUT_BITMAP_HELVETICA_18);
		break;
	case SETTINGS:
		iShowImage(0, 0, 1280, 720, bg_settings);
		//Adeeba
		iText(200, 600, "== High Scores ==", GLUT_BITMAP_TIMES_ROMAN_24);
		char str[50];
		for (int i = 0; i < 3; i++) {
			sprintf_s(str, "Level %d: %d", i + 1, highScore[i]);
			iText(200, 550 - i * 30, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		break;


		//jersey select page
	case JERSEY_SELECT:
		iShowImage(0, 0, 1280, 720, jersey_background); // jersey background 

		// Draw two jerseys side by side
		iShowImage(300, 200, 200, 200, blue); // idle frame Jersey A
		iShowImage(800, 200, 200, 200, pink); // idle frame Jersey B

		//iSetColor(255, 255, 255);
		//iText(500, 500, "Choose your Jersey!", GLUT_BITMAP_HELVETICA_18);

		// Optional highlight if hovering / already clicked
		if (selectedJersey == 1) {
			iRectangle(300, 200, 200, 200);
		}
		else if (selectedJersey == 2) {
			iRectangle(800, 200, 200, 200);
		}

		break;

		//------------------------------------------------------
		//puzzle page
	case PUZZLE:


		//*****************************************
		//puzzle page draw kortesi
		iShowImage(0, 0, 1280, 720, bg_level3);
		drawPuzzlePage();
		if (showFeedback) {
			iSetColor(255, 255, 0); // yellow
			iText(550, 600, feedbackMsg, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		//*********************************************

		// when puzzle becomes solved, immediately jump to Level 3 play
		if (solved) {
			// make sure the level state is ready, then switch
			currentState = PLAY;
			//currentLevel == 3;// (we set it when selecting the level)
			restartLevel();   // resets ball/character and sets time for level 3
		}
		break;

	default:
		break;
	}
	drawBackArrow();
}

#endif