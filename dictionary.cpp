#include "dictionary.h"
#include "utils.h"
#include <string>
#include "word.h"
#include "rd.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

// const 


void Dictionary::addWord(Word word) {
	dictionary[word.key] = word;
	wordList.push_back(word);
	index[word.key] = wordList.size() - 1;
};
void Dictionary::remWord(Word word) {
	this->remWord(word.key);
};

void Dictionary::remWord(string key) {
	dictionary.erase(key);
	int idx = index[key];
	index[wordList.back().key] = idx;
	index.erase(key);
	swap(wordList[idx], wordList.back());
	wordList.pop_back();
};

Word Dictionary::findWord(string key){
	if (dictionary.count(key)) {
		return dictionary[key];
	}
	else throw;
};
void Dictionary::load(std::string filepath) {
	this->reset();
	ifstream reader(filepath);
	string line;
	while (getline(reader, line)) {
		stringstream ss(line);
		string data;
		getline(ss, data, '|');
		string key = data;
		getline(ss, data, '|');
		string word = data;
		getline(ss, data, '|');
		string meaning = data;
		getline(ss, data, '|');
		string pronouce = data;
		getline(ss, data, '|');
		int addedTime = Utils::stringToInt(data);
		vector<Example> examples;
		getline(ss, data, '|');
		stringstream exs(data);
		string exText;
		while (getline(exs, exText, '+')) {
			stringstream smss(exText);
			string ex;
			getline(smss, ex, '=');
			string sentence = ex;
			getline(smss, ex, '=');
			string meaning = ex;
			examples.push_back(Example(sentence, meaning));
		};
		this->addWord(Word(key, word, meaning, pronouce, addedTime, examples));
	}
	this->sortByTime();
	reader.close();
};
void Dictionary::save(std::string filepath){
	ofstream os(filepath);
	if (os.is_open()) {
		for(auto word:wordList) {
			os << word << endl;
		}
	} else {
		cerr << "file problem!" << endl;
	}
	os.close();
};
void Dictionary::reset() {
	dictionary.clear();
	index.clear();
	wordList.clear();
};

int Dictionary::getSize() {
	return wordList.size();
}

Word Dictionary::getWordInWordListByIndex(int idx) {
	return wordList[idx];
}

Word Dictionary::getRandomWordUniform(int limit) {

	if (limit == -1) { limit = dictionary.size();}
	limit = min(limit, (int) wordList.size());

	int idx = Random::getRandomIndexUniform(limit);

	// cerr << idx << endl;
	return wordList[wordList.size() - limit + idx];
}


Word Dictionary::getRandomWordArithmetic(int limit, double a) {
	if (limit == -1) { limit = dictionary.size();}
	limit = min(limit, (int) wordList.size());

	int idx = Random::getRandomIndexArithmetic(limit, a);
	return wordList[wordList.size() - limit + idx];
}
Word Dictionary::getRandomWordGeometic(int limit, double multiplier) {
	if (limit == -1) { limit = dictionary.size();}
	limit = min(limit, (int) wordList.size());

	int idx = Random::getRandomIndexGeometic(limit, multiplier);
	return wordList[wordList.size() - limit + idx];
}

void Dictionary::sortByTime() {
	index.clear();
	sort(wordList.begin(), wordList.end(), [](Word word1, Word word2){
		return word1.addedTime < word2.addedTime;
	});
	for(int i = 0 ; i < wordList.size(); i++) {
		index[wordList[i].key] = i;
	}
}

ostream& operator<<(ostream& os, const Dictionary& dictionary) {
	for(auto word:dictionary.wordList) {
		os << word << endl;
	}
	return os;
}

bool Dictionary::hasWord(string key) {
	return dictionary.count(key);
}