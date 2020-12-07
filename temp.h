#ifndef TEMP_H_INCLUDED
#define TEMP_H_INCLUDED

#include <string>
#include <vector>

struct TempWord {
    int time;
    std::string word;
    TempWord(int _time, std::string _word) : time(_time), word(_word) {};
};
class TempWordListManager {
public:
    std::vector<TempWord> tempWordList;
    void loadTempWordList(std::string path);
    void saveTempWordList(std::string path);
    void addTempWord(TempWord word);
    void removeTempWord(std::string word);
    TempWord selectRandomWord();
    bool empty();
    int size();
};

#endif
