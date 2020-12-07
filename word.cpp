#include "word.h"
#include <iostream>
using namespace std;

std::ostream& operator<<(std::ostream& os, const Word& word) {
	os << word.key << "|";
	os << word.word << "|";
	os << word.meaning << "|";
	os << word.pronounce << "|";
	os << word.addedTime << "|";
	int id = 0;
	for(auto example: word.examples) {
		++id;
		os << example.sentence << "=";
		os << example.meaning << "+";
	}
	return os;
};