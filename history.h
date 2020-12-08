#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include <iostream>
#include <unordered_map>
#include <vector>
#define LEARN 0
#define PRACTICE 1
#define ADD_WORD 2
#define ADD_PARAGRAPH 3
#define ADD_TEMPORARY_WORD 4

struct HistoryDetail {
	int time;
	int action;
	std::string key; // key of word
	HistoryDetail(int _time, int _action, std::string _key): time(_time), action(_action), key(_key){};
	friend std::ostream& operator<<(std::ostream& os, const HistoryDetail& historyDetail);
};

class History {
public:
	std::unordered_map<std::string, int> count;
	std::vector<HistoryDetail> history;
	void practice(int time, std::string key);
	void learn(int time, std::string key);
	void load(std::string path);
	void save(std::string path);
	void reset();
	void addWord(int time, std::string key);
	void addParagraph(int time, std::string title);
	void add(HistoryDetail hd);
	void addTemporaryWord(int time, std::string key);
	int getFirstTime();
	int getFirstLearningTime();
	int getFrequency(std::string key);
};

#endif
