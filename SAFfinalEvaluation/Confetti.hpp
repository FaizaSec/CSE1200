#ifndef CONFETTI_HPP
#define CONFETTI_HPP

#include "Character.hpp"


struct Confetti {
	int x, y;
	int size;
	int colorR, colorG, colorB;
	int speed;
	bool active;
};

const int MAX_CONFETTI = 100;
Confetti confetti[MAX_CONFETTI];
bool showConfetti = false;
int confettiTimer = 0; // counts frames while confetti is active
const int CONFETTI_DURATION = 200; // ~200 frames (~4 seconds at 50 fps)


void initConfetti() {

	for (int i = 0; i < MAX_CONFETTI; i++) {
		confetti[i].x = rand() % 1280;          // screen width
		confetti[i].y = 720;// +rand() % 200;    // start above screen
		confetti[i].size = 5 + rand() % 6;     // size 5–10 px
		confetti[i].colorR = rand() % 256;
		confetti[i].colorG = rand() % 256;
		confetti[i].colorB = rand() % 256;
		confetti[i].speed = 2 + rand() % 3;
		confetti[i].active = true;
	}
	showConfetti = true;
}

void updateConfetti() {
	for (int i = 0; i < MAX_CONFETTI; i++) {
		if (confetti[i].active) {
			confetti[i].y -= confetti[i].speed; // move down
			confetti[i].x += (rand() % 3) - 1;

			// Reset if it goes off bottom
			if (confetti[i].y < 0) {
				confetti[i].y = 720 + rand() % 200; // same as init
				confetti[i].x = rand() % 1280;
			}
		}
	}
}


void stopConfetti() {
	showConfetti = false;
}
// Call this in level reset, quit, or pause
void resetConfetti() {
	for (int i = 0; i < MAX_CONFETTI; i++) {
		confetti[i].active = false; // deactivate all confetti
		confetti[i].x = 0;
		confetti[i].y = 0;
		confetti[i].size = 0;
		confetti[i].speed = 0;
	}
	showConfetti = false;
}

void showingConfetti()
{
	for (int i = 0; i < MAX_CONFETTI; i++) {
		if (confetti[i].active) {
			iSetColor(confetti[i].colorR, confetti[i].colorG, confetti[i].colorB);
			iFilledRectangle(confetti[i].x, confetti[i].y, confetti[i].size, confetti[i].size);
		}
	}
	updateConfetti();
	// Increase timer
	confettiTimer++;
	if (confettiTimer >= CONFETTI_DURATION) {
		showConfetti = false;   // stop showing confetti
		confettiTimer = 0;      // reset timer for next goal
	}
}
#endif