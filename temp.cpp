#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "utils.h"
#include "rd.h"
#include "temp.h"


using namespace std;

void TempWordListManager::loadTempWordList(string path) {
    ifstream reader(path);
    string line;
    while (getline(reader, line)) {
        string data;
        stringstream ss(line);
        getline(ss, data, '|');
        int time = Utils::stringToInt(Utils::trim(data));
        getline(ss, data, '|');
        string word = data;
        tempWordList.push_back(TempWord(time, data));
    }
    reader.close();
}

void TempWordListManager::saveTempWordList(string path) {
    ofstream writer(path);
    for(auto word: tempWordList) {
       writer << word.time << "|" << word.word << '\n';
    }

    writer.close();
}

void TempWordListManager::addTempWord(TempWord word) {
    tempWordList.push_back(word);
}

void TempWordListManager::removeTempWord(std::string word) {
    for(int i = 0 ; i < tempWordList.size(); i++) {
        if (tempWordList[i].word == word) {
            tempWordList.erase(tempWordList.begin() + i);
            return;
        }
    }
};

TempWord TempWordListManager::selectRandomWord() {
    int idx = Random::getRandomIndexUniform(tempWordList.size());
    return tempWordList[idx];
};


bool TempWordListManager::empty() {
    return tempWordList.size() == 0;
}

int TempWordListManager::size() {
    return tempWordList.size();
}
