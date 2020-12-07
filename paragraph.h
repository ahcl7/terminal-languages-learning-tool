#ifndef PARAGRAPH_H_INCLUDED
#define PARAGRAPH_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>

#define NEWLINE Sentence("####")
#define EMPTY_SENTENCE Sentence("")

struct Sentence {
	std::string text;
	std::string meaning;
	Sentence(std::string _text, std::string _meaning): text(_text), meaning(_meaning){};
	Sentence(std::string _text): text(_text) {};
	bool isNewlineSentence() {
		return text == "####";
	}
	friend std::ostream& operator<< (std::ostream& os, const Sentence& sentence);
};

struct Paragraph {
	std::string title;
	std::vector<Sentence> sentences;
	void loadFromRawText(std::string text);
	Paragraph(std::string _text, std::string _title);
	Paragraph(std::string _title, std::vector<Sentence> _sentences): title(_title), sentences(_sentences) {};
	std::string getText();
	std::string getMeaning();
	void doMerge(std::vector<int> mergeIdxs);
	friend std::ostream& operator<< (std::ostream& os, const Paragraph& paragraph);
};

#endif