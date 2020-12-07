#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <string>
namespace Utils {
	int stringToInt(std::string num);
	std::string toLowerCase(std::string s);
	std::string toUpperCase(std::string s);
	bool isUpperCase(char c);
	std::string trim(std::string s);
	bool isNumber(std::string s);
	std::string highlight(std::string s, std::string pattern, std::string style);
	int getNumberOfSingleWord(std::string s);
	void downloadPronouceFile(std::string word);
	int getLength(std::string s);
	int cut(int x);
};

namespace Terminal {
	void moveTo(int x, int y);
	int getWidth();
	int getHeight();
}

#endif
