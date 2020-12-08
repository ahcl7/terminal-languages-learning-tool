#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED
#include <string>
#include <vector>
#include <iostream>

struct Example {
	std::string sentence;
	std::string meaning;
	Example (std::string _sentence, std::string _meaning): sentence(_sentence), meaning(_meaning){};
};

struct Word {
	std::string key;
	std::string word;
	std::string meaning;
	std::string pronounce;
	int addedTime;
	std::vector<Example> examples;
	Word(): key(""), word(""), meaning(""), pronounce(""), addedTime(-1) {};
	Word(std::string _key, std::string _word, int _addedTime): key(_key), word(_word), meaning(""), pronounce(""), addedTime(_addedTime){};
	Word(std::string _key, std::string _word, std::string _meaning, std::string _pronounce, int _addTime, std::vector<Example> _examples):
		key(_key), word(_word), meaning(_meaning), pronounce(_pronounce), addedTime(_addTime), examples(_examples){};
	friend std::ostream& operator<<(std::ostream& os, const Word& word);
};

#endif
