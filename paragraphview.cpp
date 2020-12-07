#include "paragraphview.h"
#include "utils.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

void ParagraphView::display() {
	int curlen = 0;
	int curX = x;
	Terminal::moveTo(x, y);

	for(int i = 0; i < text.length(); i++) {
		int j = i;
		// cout << i << endl;
		int wordLen = 0;
		while (j < text.length() && (text[j] !=' ' && text[j] != '\n')) {
			if ((text[j] & 0xc0) != 0x80) { wordLen ++; };
			j++;
		}

		// cout << j << endl;
		if (curlen + wordLen >= w) {
			curlen = wordLen;
			curX++;
			Terminal::moveTo(curX, y);
		} else curlen += wordLen;
		cout << text.substr(i, j - i);
		i = j;
		while (i < text.length() && (text[i] == ' ' || text[i] == '\n')) {
			if (text[i] == '\n') {
				curX++;
				Terminal::moveTo(curX, y);
				curlen = 0;
			}
			if (text[i] == ' ') {
				curlen ++;
				if (curlen < w) {
					cout << " ";
				}
			}
			i++;
		}
		i --;
	}
}