#include "history.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include "utils.h"

using namespace std;

ostream& operator<<(ostream& os, const HistoryDetail& historyDetail) {
	os << historyDetail.time << "|" << historyDetail.action << "|" << historyDetail.key;
	return os;
}

void History::reset() {
	count.clear();
	history.clear();
}

void History::load(string path) {
	this->reset();
	ifstream reader(path);
	string line;
	while (getline(reader, line)) {
		string data;
		stringstream ss(line);
		getline(ss, data, '|');
		int time = Utils::stringToInt(Utils::trim(data));
		getline(ss, data, '|');
		int action = Utils::stringToInt(Utils::trim(data));
		getline(ss, data, '|');
		string key = Utils::trim(data);
		// add(HistoryDetail(time, action, key));
		if (action == LEARN) {
			learn(time, key);
		}
		if (action == ADDWORD) {
			addWord(time, key);
		}
		if (action == PRACTICE) {
			practice(time, key);
		}
		if (action == ADDPARAGRAPH) {
			addParagraph(time, key);
		}
	}
	reader.close();
}

void History::add(HistoryDetail hd) {
	history.push_back(hd);
}

void History::save(string path) {
	ofstream ofs(path);
	for(auto hd:history) {
		ofs << hd << endl;
	}
	ofs.close();
}

void History::learn(int _time, string key) {
	if (!~_time) add(HistoryDetail(time(0), LEARN, key));
	else add(HistoryDetail(_time, LEARN, key));
	//do nothing
}

void History::practice(int _time, string key) {
	count[key]++;
	if (!~_time)
		add(HistoryDetail(time(0), PRACTICE, key));
	else add(HistoryDetail(_time, PRACTICE, key));
}

void History::addWord(int _time, string key) {
	if (!~_time) 
		add(HistoryDetail(time(0), ADDWORD, key));
	else add(HistoryDetail(_time, ADDWORD, key));
}

void History::addParagraph(int _time, string title) {
	if (!~_time) 
		add(HistoryDetail(time(0), ADDPARAGRAPH, title));
	else add(HistoryDetail(_time, ADDPARAGRAPH, title));	
}
int History::getFirstTime() {
	if (history.size() == 0) return -1;
	return history[0].time;
}

int History::getFirstLearningTime() {
	if (history.size() == 0) return -1;
	for(auto h:history) {
		if (h.action != ADDWORD) return h.time;
	}
	return -1;
}


int History::getFrequency(string key) {
	if (count.count(key)) return count[key];
	return 0;
}