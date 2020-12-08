#include "temporary-collection.h"
#include "rd.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
void TemporaryCollection::addTemporaryWord(Word word) {
    temporaryWordList.push_back(word);
};

void TemporaryCollection::removeTemporaryWord(Word word) {
    removeTemporaryWord(word.word);
};

void TemporaryCollection::removeTemporaryWord(std::string word) {
    for(int i = 0 ; i < temporaryWordList.size(); i++) {
        if (temporaryWordList[i].word == word) {
            temporaryWordList.erase(temporaryWordList.begin() + i);
            return;
        }
    }
};

void TemporaryCollection::load(std::string path) {
    this->reset();
    ifstream reader(path);
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
        this->addTemporaryWord(Word(key, word, addedTime));
    }
    this->sortByAddedTime();
    reader.close();
};

void TemporaryCollection::sortByAddedTime() {
    auto cmp = [] (Word a, Word b) {
        return a.addedTime < b.addedTime;
    };
    sort(temporaryWordList.begin(), temporaryWordList.end(), cmp);
}

void TemporaryCollection::save(std::string path) {
    ofstream os(path);
	if (os.is_open()) {
		for(auto word:temporaryWordList) {
			os << word << endl;
		}
	} else {
		cerr << "file problem!" << endl;
	}
	os.close();
};

Word TemporaryCollection::getRandomWord(int type) {
    assert(temporaryWordList.size() > 0); // should handle case temporaryWordList.size == 0 outside
    if (type == UNIFORM) {
        int idx = Random::getRandomIndexUniform(temporaryWordList.size());
        return temporaryWordList[idx];
    } else {
        return temporaryWordList[0];
    }
};

void TemporaryCollection::reset() {
    this->temporaryWordList.clear();
}
