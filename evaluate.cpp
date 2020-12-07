#include "evaluate.h"
#include "history.h"
#include <ctime>

double f(double x) {
	double a = -0.8 / (60 * 60  - 30 * 30 * 2);
	double b = (1.0 - 60 * 60 * a) / 60.0;
	x = std::min(x, 60.0);
	return a * x * x + b * x;
}
double Evaluate::evaluate(History& history) {
	int startTime = history.getFirstLearningTime();
	if (!~startTime) return 0; //not start yet
	int curTime = time(0);
	int numberOfDays = (curTime - startTime) / (60 * 60 * 24);
	double total = 0;
	for(auto it=history.count.begin(); it != history.count.end(); it++) {
		total += f((*it).second);
	}
	return total / ((numberOfDays + 1) * 10);
}