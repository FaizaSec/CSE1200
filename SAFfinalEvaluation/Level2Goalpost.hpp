#ifndef LEVEL2GOALPOST_H
#define LEVEL2GOALPOST_H

const int NUMS_GOALPOST = 3;

//GOalpost image full header file faiza
int real_gp_images[NUMS_GOALPOST];//sky ones
int fake_gp_images[NUMS_GOALPOST];//blue ones

//goalpost position
int gp_X[NUMS_GOALPOST] = { 800, 1000, 750 };
int gp_Y[NUMS_GOALPOST] = { 0, 150, 250 };

//real goalpost index
int real_index = 0;
//for level2 background
int background2;

int background_x = 0;
int background_y = 0;

char filename2[500];

void LoadGoalpost(){

	background2 = iLoadImage("image/background2.png");

	for (int i = 0; i < NUMS_GOALPOST; i++){

		sprintf_s(filename2, "image/fake_gp%d.png", i + 1);//for fake goalpost
		fake_gp_images[i] = iLoadImage(filename2);
	}

	for (int i = 0; i < NUMS_GOALPOST; i++){

		sprintf_s(filename2, "image/real_gp%d.png", i + 1);//for real goalpost
		real_gp_images[i] = iLoadImage(filename2);
	}

	//randomly choose a goalpost
	//real_index = rand()%NUMS_GOALPOST;
}
//show goalpost images
void ShowGoalpostLevel2(){

	//iShowImage(background_x, background_y, 1280, 720, background2);

	for (int i = 0; i < NUMS_GOALPOST; i++){

		if (i == real_index){
			//draw real goalpost
			iShowImage(gp_X[i], gp_Y[i], 200, 200, real_gp_images[i]);
		}
		else
		{
			//draw fake goalpost
			iShowImage(gp_X[i], gp_Y[i], 200, 200, fake_gp_images[i]);
		}
	}
}

//reset real goalpost position 
void ResetRealGoalpost(){

	//randomly choose a goalpost
	real_index = rand() % NUMS_GOALPOST;
}

#endif