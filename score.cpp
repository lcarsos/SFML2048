#include "score.h"

#include <stdio.h>
#include <windows.h>

Score::Score() : score(0) {}

Score::Score(int num) : score(num) {}

void Score::updateScore(int num) {
	score += num;
}

int& Score::getScore() {
	return score;
}

void Score::logScore() {
	system("cls");
	printf("\rScore: %i", score);
}

void Score::resetScore() {
	system("cls");
	score = 0;
}