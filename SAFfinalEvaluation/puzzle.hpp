#ifndef PUZZLE_HPP
#define PUZZLE_HPP

//#include "Character.hpp"

bool showFeedback = false;
char feedbackMsg[32];
int feedbackTimer = 0; // frames or ms

// =====================
// Simple 4x6 Puzzle Page
// =====================

// ---- Grid config (24 tiles) ----
const int ROWS = 4;
const int COLS = 6;
const int TOTAL = ROWS * COLS;     // 24

int gridX = 175, gridY = 120;      // bottom-left of grid
int tileW = 150, tileH = 100;
int gap1 = 10;

//extern veriable
//extern int score[3];
//extern int currentLevel;


// ---- Words (instead of images) ----
const char* words[TOTAL] = {
	"messi", "offside", "yellowcard", "captain", "var", "penalty",
	"ronaldo", "referee", "goalkeeper", "pass", "formation", "manager",
	"neymar", "header", "goal", "dribble", "substitution", "tackle",
	"redcard", "assist", "midfielder", "defense", "winger", "coach"
};

int puzzleGrid[TOTAL];     // stores shuffled indices 0..23

// questions
struct Question { const char* q; const char* ans; };
Question questions[10] = {
	{ "Which means helping another player score?", "assist" },
	{ "Who makes final decisions on the field?", "referee" },
	{ "Who guards the net?", "goalkeeper" },
	{ "What’s the term for kicking to a teammate?", "pass" },
	{ "Which is shown after a serious foul?", "redcard" },
	{ "What video system reviews referee calls?", "var" },
	{ "Who is usually the team leader on field?", "captain" },
	{ "Which move uses your head?", "header" },
	{ "Which term refers to breaking offside rule?", "offside" },
	{ "What is beating an opponent with skill?", "dribble" }
};

//int totalQ = sizeof(questions) / sizeof(questions[0]);

int totalQ = 10;

// state
int currentQ = 0;
bool solved = false;


// =====================
// Puzzle helpers
// =====================
void shufflePuzzle() {
	for (int i = 0; i < TOTAL; i++) puzzleGrid[i] = i;
	for (int i = TOTAL - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int t = puzzleGrid[i]; puzzleGrid[i] = puzzleGrid[j]; puzzleGrid[j] = t;
	}
}

void initPuzzle() {
	shufflePuzzle();
	currentQ = 0;   // start from first question
	solved = false;
}


// =====================
// iGraphics callbacks
// =====================
void drawPuzzlePage() {
	// Title
	iSetColor(255, 255, 0);
	iText(500, 670, "LEVEL 3 - Football IQ Puzzle", GLUT_BITMAP_TIMES_ROMAN_24);

	// Question + progress
	iSetColor(255, 255, 255);
	if (!solved && currentQ < totalQ) {
		iText(140, 600, (char*)questions[currentQ].q, GLUT_BITMAP_TIMES_ROMAN_24);

		char prog[64];
		sprintf_s(prog, sizeof(prog), "Question %d of %d", currentQ + 1, totalQ);
		iText(980, 600, prog, GLUT_BITMAP_HELVETICA_18);
	}

	// Grid
	int idx = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++, idx++) {
			int px = gridX + c * (tileW + gap1);
			int py = gridY + r * (tileH + gap1);

			int wordIndex = puzzleGrid[idx];

			// rectangle background
			iSetColor(40, 120, 200);  // bluish box
			iFilledRectangle(px, py, tileW, tileH);

			// word text (center-ish)
			iSetColor(255, 255, 255); // white text
			iText(px + 10, py + tileH / 2, (char*)words[wordIndex], GLUT_BITMAP_HELVETICA_18);

			// border
			iSetColor(30, 30, 30);
			iRectangle(px, py, tileW, tileH);
		}
	}

	if (solved) {
		iSetColor(0, 255, 0);
		iText(420, 80, "Well Done! Puzzle Solved!", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else {
		iSetColor(200, 200, 200);
		iText(390, 80, "Click the correct word. Wrong picks shuffle the grid.", GLUT_BITMAP_HELVETICA_18);
	}
}
void puzzle_mousemove(int mx, int my){
	if (solved) return;

	int idx = 0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++, idx++) {
			int puzzleX = gridX + c * (tileW + gap1);
			int puzzleY = gridY + r * (tileH + gap1);

			if (mx >= puzzleX && mx <= puzzleX + tileW &&
				my >= puzzleY && my <= puzzleY + tileH) {

				int clickedIndex = puzzleGrid[idx];
				const char* clickedWord = words[clickedIndex];
				const char* correctWord = questions[currentQ].ans;

				if (strcmp(clickedWord, correctWord) == 0) {
					// correct
					strcpy_s(feedbackMsg, sizeof(feedbackMsg), "Correct!");
					showFeedback = true;
					feedbackTimer = 10;

					// advance
					currentQ++;
					if (currentQ >= totalQ) {
						solved = true;
					}
					else {
						shufflePuzzle();
					}
				}
				else {
					// wrong
					strcpy_s(feedbackMsg, sizeof(feedbackMsg), "Wrong!");
					showFeedback = true;
					feedbackTimer = 10;

					shufflePuzzle();
				}
				return;
			}
		}
	}
}

//--------------------------------------------
//don't know about this
void resetPuzzle() {
	currentQ = 0;      // back to first question
	solved = false;    // mark puzzle as unsolved
	shufflePuzzle();   // optional: reshuffle tiles
}


#endif