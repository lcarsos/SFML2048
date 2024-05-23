#include "score.h"

#include <stdio.h>

Score::Score() : score(0) {}

Score::Score(int num) : score(num) {}

void Score::updateScore(int num) {
	score += num;
}

int& Score::getScore() {
	return score;
}

void Score::logScore() {
	printf("\rScore: %i", score);
}

void Score::resetScore() {
	score = 0;
}
