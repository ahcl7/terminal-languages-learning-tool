#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
#include <string>
#include <iostream>
#include <unordered_map>
#include "word.h"
#define UNIFORM 0
#define ARITHMETIC 1
#define GEOMETIC 2

class Dictionary {
public:
	std::unordered_map<std::string, Word> dictionary;
	std::vector<Word> wordList;
	std::unordered_map<std::string, int> index;
	void addWord(Word word);
	void remWord(Word word);
	void remWord(std::string key);
	Word findWord(std::string key);
	void load(std::string filepath);
	void save(std::string filepath);
	void reset();
	bool hasWord(std::string key);
	int getSize();
	Word getWordInWordListByIndex(int idx);
	Word getRandomWordUniform(int limit = -1);
	Word getRandomWordArithmetic(int limit = -1, double a = 0.0);
	Word getRandomWordGeometic(int limit = -1, double multiplier = 1.0);
	friend std::ostream& operator<<(std::ostream& os, const Dictionary& dictionary);
protected:
	void sortByTime();
};

#endif