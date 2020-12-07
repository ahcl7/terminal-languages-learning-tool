#include "font.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "utils.h"


// ...


using namespace std;

void Font::load() {
	if (isDefault) return;
	ifstream reader(path);
	string line;
	vector<string> lines;
	while (getline(reader, line)) {
		lines.push_back(line);
	}
	height = (int) lines.size() / 49;
	reader.close();
	int id = 0;
	for(int i = 0 ; i < 49; i++) {
		c[i] = new string[height];
		for(int j = 0 ; j < height; j++) {
			c[i][j] = lines[id++];
		}
	}
}

int getId(char c) {
	if (c >= 'a' && c <= 'z') return c - 'a';
	if (c >= '0' && c <= '9') return 26 + c - '0';
	if (c == ':') return 36;
	if (c == ',') return 37;
	if (c == '.') return 38;
	if (c == '!') return 39;
	if (c == '?') return 40;
	if (c == '(') return 41;
	if (c == ')') return 42;
	if (c == '+') return 43;
	if (c == '-') return 44;
	if (c == '=') return 45;
	if (c == '\'') return 46;
	if (c == '\"') return 47;
	return 48;
}


vector<string> Font::getText(string text) {	

	if (isDefault) {
		vector<string> res;
		res.push_back(text);
		return res;
	}
	vector<string> res(height, "");
	text = Utils::toLowerCase(text);
	for(int i = 0 ; i <text.size(); i++) {
		for(int j = 0 ; j < height; j++) {
			res[j] += c[getId(text[i])][j];
		}
	}
	return res;
}

int getLength(string s) {
	int len = 0;
	for(int i = 0; i < s.length(); i++) if ((s[i] & 0xc0) != 0x80) len++;
	return len;
}
int Font::estimateWidth(string text) {
	if (isDefault) return getLength(text);
	int res = 0;
	for(int i = 0; i < text.length(); i++) {
		res += getLength(c[getId(text[i])][0]);
	}
	return res;
}

int Font::getHeight() {
	if (isDefault) return 1;
	return height;
}