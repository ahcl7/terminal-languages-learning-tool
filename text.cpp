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
		return (width - Utils::getLength(text)) / 2;
	}

	if (align == LEFT) {
		return 0;
	}

	if (align == RIGHT) {
		return (width - Utils::getLength(text));
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
    Terminal::moveTo(y + padding, x);
    cout << subString;
}

vector<string> Text::getSegments() {
	stringstream ss (text);
	string word;
	string curText = "";
	int padding = 0;

	vector<string> res;
	int curLen = 0;
	while (getline(ss , word, ' ')) {
		if (Utils::getLength(word) + 1 + curLen <= Terminal::getWidth()) {
			if (curText == "") curText = word;
			else curText = curText + " " + word;
			curLen += 1 + Utils::getLength(word);
		} else {
			res.push_back(curText);
			curText = word;
			curLen = Utils::getLength(word);
		}
	}
	res.push_back(curText);
	return res;
}

int Text::estimateHeight() {
	vector<string> segments = getSegments();
	return segments.size();
}

void Text::display() {
	string tmp = text;
	vector<string> segments = getSegments();
	for(int i = 0; i < segments.size(); i++) {
		displaySegment(segments[i], i);
	}
	text = tmp;
}
