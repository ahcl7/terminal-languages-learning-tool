#include "text.h"

#include <vector>
#include <string>
#include "utils.h"
#include <iostream>
#include <sstream>

using namespace std;


int Text::getX(string text) {
	int width = Terminal::getWidth();
	if (align == CENTER) {
		return (width - font.estimateWidth(text)) / 2;
	}

	if (align == LEFT) {
		return 0;
	}

	if (align == RIGHT) {
		return (width - font.estimateWidth(text));
	}

	return 0;
}
int Text::getX() {
	return getX(text);
	
}


void Text::highlight(string _pattern, string _style) {
	pattern = _pattern;
	style = _style;
}
void Text::displaySegment(string subString, int padding) {
	
	int x = getX(subString);
	
	if (style != "" && pattern != "") {
		Terminal::moveTo(y + padding, x);
		string txt = Utils::highlight(subString, pattern, style);
		cout << txt;
		return;
	}
	vector<string> lines = font.getText(subString);
	for(int i = 0; i < lines.size(); i++) {
		Terminal::moveTo(y + i + padding, x);
		cout << lines[i];
	}
}

vector<string> Text::getSegments() {
	stringstream ss (text);
	string word;
	string curText = "";
	int padding = 0;

	vector<string> res;
	while (getline(ss , word, ' ')) {
		if (font.estimateWidth(curText + " " + word) <= Terminal::getWidth()) {
			if (curText == "") curText = word;
			else curText = curText + " " + word;
		} else {
			res.push_back(curText);
			curText = word;
		}
	}
	res.push_back(curText);
	return res;
}

int Text::estimateHeight() {
	vector<string> segments = getSegments();
	return (font.getHeight() + 1) * segments.size();
}

void Text::display() {
	string tmp = text;
	if (!font.isDefault) {
		tmp = text;
		text = Utils::unicodeToAscii(text);
	}
	// text = "arithmetic progression";
	// cout << text << endl;
	vector<string> segments = getSegments();
	// cout << segments.size() << endl;
	// for(auto s:segments) cout << s << endl;
	for(int i = 0; i < segments.size(); i++) {
		displaySegment(segments[i], i * (font.getHeight() + 1));
	}
	text = tmp;
}