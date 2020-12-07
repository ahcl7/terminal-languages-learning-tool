#ifndef RD_H_INCLUDED
#define RD_H_INCLUDED

namespace Random {
	int getRandomIndex(double* probabilities, int n);
	int getRandomIndexUniform(int n);
	int getRandomIndexArithmetic(int n, double a = 0.0);
	int getRandomIndexGeometic(int n, double multiplier = 1.0);
	int getRandomIndexPrioritizeForLowFrequency(int* fre, int n);
	double nextDouble();
}

#endif