#ifndef JERSEYCHOOSE_HPP
#define JERSEYCHOOSE_HPP

int characterImagesBlue[6]; // Jersey Blue sprite sheet 
int characterImagesPink[6]; // Jersey Pink sprite sheet 

int jersey_background;
int blue, pink;//jersey select screen e j image show koebe

int selectedJersey = 0;
int* currentCharacterImages = nullptr; // Pointer to the sprite sheet for the chosen jersey

void loadJerseyImages() {
	for (int i = 0; i < 6; i++) {

		char filenameblue[64], filenamepink[64];

		sprintf_s(filenameblue, "Image/bluechar%d.png", i + 1);//for blue 

		sprintf_s(filenamepink, "Image/pinkchar%d.png", i + 1);//for pink

		characterImagesBlue[i] = iLoadImage(filenameblue);//for blue 

		characterImagesPink[i] = iLoadImage(filenamepink);//for pink
	}

	//jersey color character load
	jersey_background = iLoadImage("image/jerseybackground.png");

	//jersey select
	blue = iLoadImage("image/bluejersey.png");
	pink = iLoadImage("image/pinkjersey.png");

}


#endif