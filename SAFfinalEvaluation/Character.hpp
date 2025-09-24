#ifndef CHARACTER_H
#define CHARACTER_H

#include "GoalPost.hpp"
#include "Variable.hpp"
#include "Level2Goalpost.hpp"
#include "Confetti.hpp"
#include "jerseychoose.hpp"
#include "puzzle.hpp"
#include "Confetti.hpp"
#include "Keeper.hpp"
// Game states
enum GameState { SPLASH, MENU, LEVEL_SELECT, JERSEY_SELECT, PLAY, PUZZLE, INSTRUCTIONS, ABOUT, SETTINGS, EXIT };
GameState currentState = SPLASH; // Start from splash

goalpost goal;
keeper gk;
int score[3] = { 0, 0, 0 };
int highScore[3] = { 0, 0, 0 };
int gameTime[3] = { 60, 30, 90 };

bool showGoalText = false, goal_scored = false;
int goalTextY = 0, goalTextTimer = 0;

//time method shova
void updateTime() {
	if (!gamePaused && !gameOver && gameTime[currentLevel - 1] > 0) {
		//new approach
		int timeRemaining = gameTime[currentLevel - 1]--;
		if (gameTime[currentLevel - 1] == 0) {
			gameOver = true;
		}
	}
}
// Reset ball near character's feet shova
void resetBallToCharacterFeet() {
	ball_x = characterX + 60;  // More forward (character is 100px wide)
	ball_y = characterY + 10;
	ball_vx = 0;
	ball_vy = 0;
	ball_moving = false;
	ballAttached = true;
}
//character returning to it's original place shova
void resetCharacterPosition() {
	characterX = 100;
	characterY = 100;
	characterIndex = 0;
	printf("Boundary hit! Resetting to (100,100)\n");
}
//mouse move to detach the ball logic faiza
void ballDetachment(int mx, int my){
	// Only allow kick if ball is close to character
	double dx = mx - ball_x;
	double dy = my - ball_y;

	double distToCharacter = sqrt((ball_x - characterX) * (ball_x - characterX) +
		(ball_y - characterY) * (ball_y - characterY));

	if (distToCharacter < 100) {

		double length = sqrt(dx * dx + dy * dy);
		ball_vx = 7 * (dx / length);
		ball_vy = 7 * (dy / length);
		ball_moving = true;
		ballAttached = false;
		resetCharacterPosition();
	}
}
// Floating GOAL text adeeba
void goalText(){
	if (showGoalText) {
		goalTextY += 1;
		goalTextTimer--;
		if (goalTextTimer <= 0) {
			showGoalText = false;
			goal_scored = false;
		}
	}
}

//Faiza+Shova
void move_ball() {// Ball physics update+collision logic
	//new
	if (currentState != PLAY || gamePaused || gameOver) return;
	if (ball_moving) {
		//theta += .05;
		//ball_x += cx + r * cos(theta) + ball_vx;
		//ball_y += cy + r * sin(theta) + ball_vy;
		ball_x += ball_vx;
		ball_y += ball_vy;
		//collision logic for level 1
		if (currentLevel == 1){
			if ((ball_x + ball_width) >= (goal.goalpost_x + 90) && ball_x <= (goal.goalpost_x + goalpost_width) - 100
				&& (ball_y + ball_height) >= (goal.goalpost_y + 120) && ball_y <= (goal.goalpost_y + goalpost_height) - 110)
			{
				ball_moving = false;
				resetBallToCharacterFeet();
				goal_scored = true;
				score[currentLevel - 1]++;
				showGoalText = true;
				goalTextY = goal.goalpost_y + goalpost_height;
				goalTextTimer = 30;//new time
				mciSendString("play goalsound from 0", NULL, 0, NULL);
				// Confetti
				showConfetti = true;
				confettiTimer = 0;
				initConfetti();
			}
		}//add level 2 collision after this
		else if (currentLevel == 2){

			//here give the collision logic for level2
			ResetRealGoalpost();
			int gpX = gp_X[real_index];
			int gpY = gp_Y[real_index];
			int gpWidth = 200;
			int gpHeight = 200;

			int offsetLeft = 90;
			int offsetRight = 100;
			int offsetTop = 120;
			int offsetBottom = 110;

			int ball_left = ball_x - ball_width;
			int ball_right = ball_x;
			int ball_bottom = ball_y;
			int ball_top = ball_y + ball_height;

			if ((ball_right >= gpX + offsetLeft) && (ball_left <= gpX + gpWidth - offsetRight) && (ball_top >= gpY + offsetTop) &&
				(ball_bottom <= gpY + gpHeight - offsetBottom)) {
				ball_moving = false;
				resetBallToCharacterFeet();
				goal_scored = true;
				score[currentLevel - 1]++;
				showGoalText = true;
				goalTextY = gpY + gpHeight;
				goalTextTimer = 30;
				mciSendString("play goalsound from 0", NULL, 0, NULL);

				// Confetti
				showConfetti = true;
				confettiTimer = 0;
				initConfetti();
				// Pick a new real goalpost for next shot
				ResetRealGoalpost();
			}
		}
		else if (currentLevel == 3)
		{
			// ---------------- Keeper Collision ----------------
			if ((ball_x + ball_width) >= gk.keeperX && ball_x <= (gk.keeperX + keeper_width)
				&& (ball_y + ball_height) >= gk.keeperY && ball_y <= (gk.keeperY + keeper_height))
			{
				ball_moving = false;
				resetBallToCharacterFeet();
				ball_saved = true;   // saved by keeper
				//showSaveText = true;
				//saveTextY = gk.keeperY + keeper_height;
				//saveTextTimer = 30;

				//mciSendString("play savesound from 0", NULL, 0, NULL);
			}
			// ---------------- Goal Collision ----------------
			else if ((ball_x + ball_width) >= (gp3X + 90) && ball_x <= (gp3X + goalpost_width) - 100
				&& (ball_y + ball_height) >= (gp3Y + 120) && ball_y <= (gp3Y + goalpost_height) - 110)
			{
				ball_moving = false;
				resetBallToCharacterFeet();
				goal_scored = true;
				score[currentLevel - 1]++;
				showGoalText = true;
				goalTextY = goal.goalpost_y + goalpost_height;
				goalTextTimer = 30;

				mciSendString("play goalsound from 0", NULL, 0, NULL);

				// Confetti
				showConfetti = true;
				confettiTimer = 0;
				initConfetti();
			}
		}


		// Out of bounds works for every level
		//jodi iStart() call korte korte jodi screen er baire chole jai
		if ((ball_x + ball_width) >= 1280 || (ball_y + ball_height) >= 720 || ball_y <= 0)
		{
			//ball_vx = -ball_vx;
			//ball_vy = -ball_vy;
			ball_x += ball_vx;
			ball_y += ball_vy;
			ball_moving = false;
			resetBallToCharacterFeet();
		}
	}
}
//restart any level shova
void restartLevel() {
	if (currentLevel > 0) {
		if (score[currentLevel - 1] > highScore[currentLevel - 1]){
			highScore[currentLevel - 1] = score[currentLevel - 1];
		}
		// Reset character and ball
		resetCharacterPosition();
		resetBallToCharacterFeet();
		ResetRealGoalpost();//level 2
		resetConfetti();

		// Reset score and timer for this level
		score[currentLevel - 1] = 0;
		if (currentLevel == 1){//new 
			gameTime[currentLevel - 1] = 60;
		}
		if (currentLevel == 2){
			gameTime[currentLevel - 1] = 30;
		}
		if (currentLevel == 3){
			gameTime[currentLevel - 1] = 90;
		}
		gameOver = false;
		gamePaused = false;
		printf("Level %d restarted!\n", currentLevel);
	}
}
//quit any level shova
void quitToLevelSelect() {
	if (score[currentLevel - 1] > highScore[currentLevel - 1]){
		highScore[currentLevel - 1] = score[currentLevel - 1];
	}
	gamePaused = false;
	gameOver = false;
	currentState = LEVEL_SELECT;
	currentLevel = 0; // no level active
}
//new funtion

#endif