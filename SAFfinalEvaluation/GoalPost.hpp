#ifndef GOALPOST_H
#define GOALPOST_H

const int goalpost_width = 250;
const int goalpost_height = 250;
const int goalpost_max_speed = 10;

//goal hoar por goalpost stop korar jonno boolean
extern bool goal_scored;
struct goalpost{

	int goalpost_x;
	int goalpost_y;

	int speed_x;
	int speed_y;
	int image;// declare korlam pore jodi lage

	//goalpost er apatoto x y coordinate
	void init()
	{
		goalpost_x = 800;
		goalpost_y = 0;

		speed_x = 5;
		speed_y = 7;

	}

	//goalpost x and y movement korar function
	void moveGp1()
	{
		if (!goal_scored)// etate goal na hoile goalpost move korbe still
		{
			goalpost_x += speed_x;
			goalpost_y += speed_y;

			//function call
			resetGoalpost();
		}

	}

	//goalpost boundary te touch korle reset hobe maybe oi function
	void resetGoalpost()
	{
		if (goalpost_x <= 700 || (goalpost_x + goalpost_width) >= 1280){

			speed_x = -speed_x;


		}
		if (goalpost_y <= 0 || (goalpost_y + goalpost_height) >= 440){

			speed_y = -speed_y;

		}

	}
};

#endif