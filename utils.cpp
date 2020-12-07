#include "utils.h"
#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
using namespace std;

std::unordered_map<wchar_t, char> ma;

int Utils::stringToInt(std::string num) {
	int res = 0;
	for(int i = 0; i < num.length(); i++) {
		if (num[i] >= '0' && num[i] <= '9') res = res * 10 + num[i] - '0';
	}
	return res;
}

std::string Utils::toLowerCase(std::string s) {
	for(int i = 0 ; i < s.length(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = s[i] - 'A' + 'a';
		}
	}
	return s;
}

std::string Utils::toUpperCase(std::string s) {
	for(int i = 0 ; i < s.length(); i++) {
		if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] = s[i] - 'a' + 'A';
		}
	}
	return s;
}

std::string Utils::trim(std::string s) {
	int l = 0;
	while (l < s.length() && (s[l] == ' ' || s[l] == '\n')) l++;
	int r = s.length() - 1;
	while (r >= 0 && (s[r] == ' ' || s[r] == '\n')) r--;
	if (r == -1) return "";
	return s.substr(l, r - l + 1);
}

int Utils::getNumberOfSingleWord(std::string s) {
	s = trim(s);
	int res = 1;
	for(int i = 0 ; i < s.length(); i++) {
		if (s[i] == ' ') res ++;
	}
	return res;
}

void Utils::downloadPronouceFile(std::string word) {
	stringstream ss;
	ss << "wget https://ssl.gstatic.com/dictionary/static/sounds/oxford/";
	ss << word;
	ss << "--_gb_1.mp3 -P ./procounces";
	system(ss.str().c_str());
}

bool Utils::isNumber(std::string s) {
	s = trim(s);
	int l = 0 ;
	while (l < s.length() && s[l] == '0') l++;
	if (l == s.length()) return false;
	s = s.substr(l, s.length() - l);
	long long t = 0;
	if (s.length() > 10) return false;
	for(int i = 0 ;i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9') return false;
		t = t * 10 + s[i];
	}

	return t < (1ll << 31);
}

bool Utils::isUpperCase(char c) {
	return c >= 'A' && c <= 'Z';
}

void Terminal::moveTo(int x, int y) {
	std::stringstream ss;
	ss << "\033[";
	ss << x;
	ss << ";";
	ss << y;
	ss << "H";
	std::cout << ss.str();
}

int Utils::cut(int x) {
	return (x & ((1 << 8) - 1));
}

string Utils::highlight(string s, string pattern, string style) {
	string res = "";
	for(int i = 0 ; i < s.length(); i++) {
		if (i + pattern.length() <= s.length() && s.substr(i, pattern.length()) == pattern) {
			res += style;
			res += pattern;
			res += "\033[0m";
			i += pattern.length() - 1;
		} else {
			res += s[i];
		}
	}
	return res;
}

int Utils::getLength(std::string s) {
    int len = 0;
    for(int i = 0; i < s.length(); i++) if ((s[i] & 0xc0) != 0x80) len++;
    return len;
}

int Terminal::getWidth() {
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int width = size.ws_col;
	return width;
}

int Terminal::getHeight() {
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int height = size.ws_row;
	return height;
}

