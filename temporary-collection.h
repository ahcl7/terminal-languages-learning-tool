#ifndef TEMPORARY_H_INCLUDED
#define TEMPORARY_H_INCLUDED

#include "word.h"
#define UNIFORM 1
#define ORDER_BY_TIME 2
class TemporaryCollection {
private:
    std::vector<Word> temporaryWordList;
    void sortByAddedTime();
public:
    void addTemporaryWord(Word word);
    void removeTemporaryWord(Word word);
    void removeTemporaryWord(std::string word);
    void load(std::string path);
    void save(std::string path);
    Word getRandomWord(int type);
    void reset();
    int size(){ return temporaryWordList.size();}
};

#endif
