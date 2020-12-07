#include "collection.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

void Collection::reset() {
	pList.clear();
}
void Collection::load(string path) {
	this->reset();
	ifstream reader(path);
	string line;
	pList.clear();
	while (getline(reader, line)) {
		std::vector<Sentence> sentences;
		stringstream ss(line);
		string data;
		getline(ss, data, '|');
		string title = data;
		while (getline(ss, data, '|')) {
			stringstream sss(data);
			string text;
			string meaning;
			getline(sss, text, '=');
			getline(sss, meaning, '=');
			sentences.push_back(Sentence(text, meaning));
		}
		pList.push_back(Paragraph(title, sentences));
	}
	reader.close();
}

void Collection::save(string path) {
	ofstream ofs(path);
	for(auto& p:pList) {
		ofs << p << endl;
	}
	ofs.close();
}
void Collection::add(Paragraph paragraph) {
	pList.push_back(paragraph);
}
int Collection::getSize() {
	return pList.size();
}