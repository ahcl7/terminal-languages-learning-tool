#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

struct Score {
	std::string day;
	double score;
	Score(std::string _day, double _score): day(_day), score(_score) {};	
};

#endif