#ifndef TIMEMANAGER_H_INCLUDED
#define TIMEMANAGER_H_INCLUDED

#include <string>
class TimeManager {
private:	
	int startTime;
public:
	void start();
	void end(std::string message);
};

#endif