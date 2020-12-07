#include "timemanager.h"
#include <ctime>
#include <iostream>
#include <string>

void TimeManager::start() {
	startTime = time(0);
}

void TimeManager::end(std::string message) {
	int end = time(0);
	std::cout << message << end - startTime << " ms" << std::endl;
}