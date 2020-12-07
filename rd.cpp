#include "rd.h"
#include <random>
#include <ctime>
#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;
std::mt19937 generator(time(0));
int Random::getRandomIndex(double* probabilities, int n) {
	double total = 0;
	for(int i = 0 ; i < n ; i ++) {
		total += probabilities[i];
	}

	double p[n];
	for(int i = 0 ; i < n ; i ++) p[i] = ((i == 0 ) ? 0.0 : p[i-1]) + probabilities[i] / total;
	double x = nextDouble();
	int res =  std::lower_bound(p, p + n, x) - p;
	return res;
}

int Random::getRandomIndexUniform(int n) {
	return generator() % n;
}

int Random::getRandomIndexArithmetic(int n, double a) {
	double p[n];
	if (n == 1) {
		p[0] = 1.0;
	} else {
		p[0] = (2.0 / n - a * (n - 1)) / 2.0;
		for(int i = 1; i < n; i++) {
			p[i] = p[i-1] + a;
		}
	}
	return getRandomIndex(p, n);
}

int Random::getRandomIndexGeometic(int n, double multiplier) {
	double p[n];
	if (n == 1) {
		p[0] = 1.0;
	} else {
		p[0] = (1.0 - multiplier) / (1.0 - pow(multiplier, n));
		for(int i = 1; i < n; i++) {
			p[i] = p[i-1] * multiplier;
		}
	}
	return getRandomIndex(p, n);
}

int Random::getRandomIndexPrioritizeForLowFrequency(int* fre, int n) {
	double p[n];
	int Ma = 0;
	for(int i = 0 ;i < n; i++) Ma = max(Ma, fre[i]);
	for(int i = 0 ; i < n; i++) {
		p[i] = Ma - fre[i];
	}

	return getRandomIndex(p, n);
}

double Random::nextDouble() {
	return 1.0 * generator() / (1ll << 32);
}