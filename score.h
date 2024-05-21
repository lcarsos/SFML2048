#pragma once


#ifndef SCORE_H
#define SCORE_H

class Score {
public:
	Score();

	Score(int initVal);

	void updateScore(int num);

	int getScore();

	void logScore();

	void resetScore();


private:
	int score;


};

#endif