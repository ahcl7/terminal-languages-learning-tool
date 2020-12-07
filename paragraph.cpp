#include "paragraph.h"
#include "utils.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;


int getNextCharacter(string s, int pos) {
	while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n')) {
		pos++;
	}
	if (pos == s.length()) return ' ';
	else {
		int cur = Utils::cut(s[pos]);
		pos++;
		while (pos < s.length() && (s[pos] & 0xc0) == 0x80) {
			cur = (cur << 8) | Utils::cut(s[pos]);
			pos++;
		}
		return cur;
	}
}

void Paragraph::loadFromRawText(string text) {
	sentences.clear();
	int l = 0;
	bool started = false;
	text = Utils::trim(text); //remove all \n character in the end of paragraph
	for(int i = 0; i < text.length(); i++) {
		if (text[i] == '\n') sentences.push_back(NEWLINE); //never add newline for last sentence thanks to above trim
		if (!started) {
			l = i;
			if (text[i] == ' ' || text[i] == '\n') l = i;
			else {
				started = true;
			}
		}
		if (text[i] == '.' || text[i] == '?' || text[i] == '!') {
			int nxtC = getNextCharacter(text, i + 1);
			if (i == text.length() - 1 || Utils::isUpperCase(nxtC)) { //['.','?','!'] follows by an Uppercase character
				sentences.push_back(Sentence(text.substr(l, i - l + 1)));
				l = i + 1;
				started = false;
			}
			if (text[i] == '.' && (nxtC == '"' )){//|| nxtC == '“')) {
				sentences.push_back(Sentence(text.substr(l, i - l + 1)));
				l = i + 1;
				started = false;
			}
		}
	}

	if (started) {
		int r = text.length() - 1;
		while (r >= 0 && (text[r] == ' ' || text[r] == '\n')) r--;
		if (l <= r) sentences.push_back(Sentence(text.substr(l, r - l + 1)));
	}
}

Paragraph::Paragraph(string text, string _title): title(_title) {
	loadFromRawText(text);
}

ostream& operator<< (ostream& os, const Sentence& sentence) {
	os << sentence.text << "=" <<sentence.meaning;
	return os;
}
ostream& operator<< (ostream& os, const Paragraph& paragraph) {
	os << paragraph.title << "|";
	for(auto& s:paragraph.sentences) {
		os << s << "|";
	}
	return os;
}

string Paragraph::getText() {
	string res = "";
	for(auto& s:sentences) {
		if (s.isNewlineSentence()) {
			res += "\n";
		} else res += s.text;
	}

	return res;
}

void Paragraph::doMerge(std::vector<int> mergeIdxs) {
	vector<Sentence> newSentences;
	int id = 0;
	for(int i = 0 ; i < sentences.size(); i++) {
		newSentences.push_back(EMPTY_SENTENCE);
		int k = 0;
		while (id + k < mergeIdxs.size() && i + k == mergeIdxs[id + k]) {
			newSentences.back().text += sentences[i + k].text;
			k++;
		}
		newSentences.back().text += sentences[i + k].text;
		i += k;
		id += k;
	}
	sentences = newSentences;
}

string Paragraph::getMeaning() {
	string res = "";
	for(auto& s:sentences) {
		if (s.isNewlineSentence()) {
			res += "\n";
		} else res += s.meaning;
	}

	return res;
}