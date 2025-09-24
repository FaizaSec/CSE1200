#ifndef KEEPER_H
#define KEEPER_H

#include "GoalPost.hpp"

const int keeper_height = 150;
const int keeper_width = 100;
const int keeper_max_speed = 5;

struct keeper{
	int keeperX;
	int keeperY;
	int speedX;
	int speedY;
	int image[2];
	int frame;

	void init()
	{
		keeperX = 900;
		keeperY = 150;
		speedX = 1;
		speedY = 3;
	}
	//keeper X e move
	void moveKeeper()
	{
		if (!goal_scored)// etate goal na hoile goalpost move korbe still
		{
			if (ball_moving){
				keeperX += speedX;
				keeperY += speedY;
			}
			else{
				keeperY += speedY;
			}
		}resetKeeper();
		static int counter = 0;
		counter++;
		if (counter >= 10) {  // change frame every 10 updates
			frame = (frame + 1) % 2;
			counter = 0;
		}
	}


	void resetKeeper()
	{
		// Horizontal boundary (goalpost X: 950 to 1300)
		if (keeperX <= 950) {
			keeperX = 950;        // clamp
			speedX = -speedX;     // reverse
		}
		else if (keeperX + 100 >= 1230) {
			keeperX = 1000;       // clamp (1300 - width)
			speedX = -speedX;
		}

		// Vertical boundary (goalpost Y: 150 to 400)
		if (keeperY <= 150) {
			keeperY = 150;
			speedY = -speedY;
		}
		else if (keeperY + 100 >= 300) {
			keeperY = 200;        // clamp (400 - height)
			speedY = -speedY;
		}

	}

};

#endif