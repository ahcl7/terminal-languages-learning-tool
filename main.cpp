#include "utils.h"
#include "timemanager.h"
#include "word.h"
#include "dictionary.h"
#include "collection.h"
#include "paragraphview.h"
#include "font.h"
#include "text.h"
#include "history.h"
#include "evaluate.h"
#include "setting.h"
#include "cons.h"
#include "rd.h"
#include "paragraph.h"
#include "ctime"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include<ios>      
#include<limits>  
#include <sys/types.h>
#include <sys/stat.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;

string getDataPath(string language) { return "./data/" + language + "/data.txt"; }
string getHistoryPath(string language) { return "./data/" + language + "/history.txt"; }
string getCollectionPath(string language) { return "./data/" + language + "/collection.txt"; }


const Font DEFAULT_FONT = Font("./fonts/default.font");
const Font HUGE_FONT = Font("./fonts/huge.font", false);
const Font MEDIUM_FONT = Font("./fonts/medium.font", false);
const Font SMALL_FONT = Font("./fonts/small.font", false);
const Font BIG_FONT = Font("./fonts/big.font", false);

void showMenu() {
	cout << "Choose command: " << endl;
	cout << "1. Add new word" << endl;
	cout << "2. Learn" << endl;
	cout << "3. Practice" << endl;
	cout << "4. Enter paragraph" << endl;
	cout << "5. Show paragraph" << endl;
	cout << "6. Setting" << endl;
}

void clearScreen() {
	cout << "\033[2J\033[1;1H";
}


	
void showDictionary(Dictionary& dictionary) {
	cout << dictionary << endl;
}

void enterLine(string& s) {
	getline(cin, s);
}

string enterLine() {
	string s;
	enterLine(s);
	return s;
}

Word getRandomWord(Dictionary& dictionary, History& history, Setting& setting) {
	double k = Random::nextDouble();
	if (k < setting.lRate) {
		int range = min((int) dictionary.getSize(), (setting.nLast == -1) ? dictionary.getSize() : setting.nLast);
        int idx = Random::getRandomIndexUniform(range);
        return dictionary.getWordInWordListByIndex(dictionary.getSize() - 1 - idx);
    } else {
        int* cnt = new int[dictionary.getSize()];
        for(int i = 0 ; i < dictionary.getSize(); i++) {
        	string key = dictionary.getWordInWordListByIndex(i).key;
        	cnt[i] = history.getFrequency(key);
        }
        int idx = Random::getRandomIndexPrioritizeForLowFrequency(cnt, dictionary.getSize());
        return dictionary.getWordInWordListByIndex(idx);
    }
}


void loadData(Dictionary& dictionary, History& history, Collection& collection, Setting& setting) {
	TimeManager timemanager = TimeManager();
	cout << "Loading data from local...!" << endl;
	timemanager.start();
	dictionary.load(getDataPath(setting.language));
	history.load(getHistoryPath(setting.language));
	collection.load(getCollectionPath(setting.language));
	cout << "Loading done!" << endl;
	timemanager.end("Loading time: ");
}

void save(Dictionary& dictionary, History& history, Setting& setting) {
	cout << "Saving data..." << endl;
	dictionary.save(getDataPath(setting.language));
	history.save(getHistoryPath(setting.language));
	cout << GREEN << "Saved" << RESET << endl;
}

void addWord(Dictionary& dictionary, History &history, Setting& setting) {
	string word, meaning, pronounce;
	int addedtime = time(0);
	vector<Example> examples;
	cout << "Enter new word!" << endl;
	cout << "Word: "; enterLine(word); word = Utils::trim(word);

	if (dictionary.hasWord(word)) {
		cout << RED << "This word is already exist! Please enter another word!" << RESET << endl;
		return;
	}
	cout << "Meaning: "; enterLine(meaning); meaning = Utils::trim(meaning);
	cout << "pronounce: "; enterLine(pronounce); pronounce = Utils::trim(pronounce);
	cout << "Examples: ";
	while (true) {
		cout << "Do you want to enter more example?"; string response; enterLine(response);
		response = Utils::toLowerCase(Utils::trim(response));
		if (response == "y" || response == "yes") {
			cout << "Example: "; string sentence; enterLine(sentence); sentence = Utils::trim(sentence);
			cout << "Meaning: "; string eMeaning; enterLine(eMeaning); eMeaning = Utils::trim(eMeaning);
			examples.push_back(Example(sentence, eMeaning));
		} else {
			cout << GREEN << "Stop entering examples!" << RESET << endl;
			break;
		}
	}
	dictionary.addWord(Word(word, word, meaning, pronounce, addedtime, examples));
	history.addWord(-1, word);
	save(dictionary, history, setting);
	cout << "Word " << GREEN << word << RESET <<" is added!"  << endl;
	if (Utils::getNumberOfSingleWord(word) == 1) {
		Utils::downloadPronouceFile(word);
	} 

}

void displayWord(Word& word, string type) {
	clearScreen();	
	int y = Terminal::getHeight() / 2;
	if (type == "1") {
		Text wordText = Text(word.word, DEFAULT_FONT, CENTER, y);
		wordText.display();
	}
	if (type == "2") {
		Text meaningText = Text(word.meaning, DEFAULT_FONT, CENTER, y );
		meaningText.display();
	}
	if (type == "3") {
		for(auto example:word.examples) {
			Text sText = Text(example.sentence, DEFAULT_FONT, CENTER, y ++);
			Text mText = Text(example.meaning, DEFAULT_FONT, CENTER, y ++); y++;
			sText.highlight(word.word, "\033[34m");
			sText.display();
			mText.display();
		}
	}
	if (type == "4") {
		Text meaningText = Text(word.pronounce, DEFAULT_FONT, CENTER, y );
		meaningText.display();	
	}
}

void learn(Dictionary& dictionary, History& history, Setting setting) {
	cout << "Start to learn..." << endl;

	if (dictionary.getSize() == 0) {
		cout << "\033[31mDictionary is empty!\033[0m" << endl;
		return;
	}
	Word word;
	int cnt = 0;
	while (true) {
		// cout << "continue? ";
		string response; enterLine(response);
		response = Utils::toLowerCase(Utils::trim(response));
		if (response == "n" || response == "next" || response == "") {
			word = getRandomWord(dictionary, history, setting);
			displayWord(word, "1");
			history.learn(-1, word.key);
			cnt ++;
			if (cnt == 10) {
				history.save(getHistoryPath(setting.language));
				cnt = 0;
			}
		} else {
			if (response == "1" || response == "2" || response == "3" || response == "4") {
				displayWord(word, response);
			} else break;
		}
		Terminal::moveTo(Terminal::getHeight() - 1, 0);
	}
	history.save(getHistoryPath(setting.language));
}

void practice(Dictionary& dictionary, History& history, Setting setting) {
	cout << "Start to practice..." << endl;
	if (dictionary.getSize() == 0) {
		cout << "\033[31mDictionary is empty!\033[0m" << endl;
		return;
	}
	Word word;
	int cnt = 0;
	while (true) {
		string response; enterLine(response);
		response = Utils::toLowerCase(Utils::trim(response));
		if (response == "n" || response == "next" || response == "") {
			word = getRandomWord(dictionary, history, setting);
			displayWord(word, "2");
			int y = Terminal::getHeight() / 2 + 2;
			int x = Terminal::getWidth() / 2 - 10;
			Terminal::moveTo(y, x);
			string answer = Utils::trim(enterLine());
			if (answer == word.word) {
				history.practice(-1, word.key);
				Terminal::moveTo(y + 2, x);
				cout << "\033[32mCorrect!\033[0m" << endl;
				Terminal::moveTo(y + 3, x);
				cout << "Score: " << Evaluate::evaluate(history);
				cnt ++;
				if (cnt == 10) {
					history.save(getHistoryPath(setting.language));
					cnt = 0;
				}
			} else {
				Terminal::moveTo(y + 2, x - 11);
				cout << "\033[31mIncorrect! \033[0m\033[21m" << word.word << "\033[0m is the correct answer!";
			}
		} else {
			if (response == "1" || response == "2" || response == "3" || response == "4") {
				displayWord(word, response);
			} else break;
		}
		Terminal::moveTo(Terminal::getHeight() - 1, 0);
	}
	history.save(getHistoryPath(setting.language));
}

int enterNumber(int min, int max) {
	cout << "Enter your choice: [" << min <<", " << max << "] ";
	while (true) {
		string s;

		enterLine(s);
		if (Utils::isNumber(s)) {
			int k = Utils::stringToInt(s);
			if (k >= min && k <= max) {
				return k;
			}
		}
		cout << RED << "Not valid, please enter again: " << RESET;
	}
}

bool checkLanguage(string language) {
	struct stat info;
	string path = "./data/" + language;
	if (stat(path.c_str(), &info) != 0) return false;
	return true;
}

void changeSetting(Dictionary& dictionary, History& history, Collection& collection, Setting& setting) {
	while (true) {
		string command = enterLine();
		stringstream ss(command);
		string action; ss >> action; action = Utils::toLowerCase(action);
		if (action == "set") {
			string param; ss >> param; param = Utils::toLowerCase(param);
			if (param == "nlast") {
				int value; ss >> value;
				if (value >= -1 && value != 0) {
					setting.nLast = value;
					cout << GREEN << "ok!" << RESET << endl;
				} else {
					cout << RED << "Invalid value!" << RESET << endl;
				}
			} 
			if (param == "lrate") {
				double value; ss >> value;
				if (value >= 0 && value < 1.0) {
					setting.lRate = value;
					cout << GREEN << "ok!" << RESET << endl;
				} else {
					cout << RED << "Invalid value! Value should be in range [0, 1)" << RESET << endl;
				}
			}
			if (param == "language") {
				string lg; ss >> lg;
				bool ok = checkLanguage(lg);
				if (!ok) {
					cout << "This language hasn't been created yet! Do you want to continue to learning this language? ";
					string response; response = Utils::trim(enterLine());
					if (response == "y" || response == "yes") {
						ok = true;
					}
				}
				if (ok) {
					setting.language = lg;
					loadData(dictionary, history, collection, setting);
				}
			}
		}
		if (action == "stop") {
			break;
		}
		if (action == "show") {
			string param; ss >> param; param = Utils::toLowerCase(param);
			if (param == "all") {
				cout << setting << endl;
			}
			if (param == "nlast") {
				cout << setting.nLast << endl;
			}
			if (param == "lrate") {
				cout << setting.lRate << endl;
			}
			if (param == "language") {
				cout << setting.language << endl;
			}
		}
	}
}

void enterParagraph(Dictionary& dictionary, History& history, Collection& collection, Setting& setting) {
	string text;
	string title;
	cout << "Enter the title: ";
	title = Utils::trim(enterLine());
	getline(cin, text, '~');
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cout << "==================" << endl;
	cout << text << endl;

	cout << "==================" << endl;

	Paragraph paragraph = Paragraph(text, title);

	// seperate paragraph sentence by sentece

	vector<int> mergeIdxs;
	for(int i = 0; i < paragraph.sentences.size() - 1; i++) {
		cout << GREEN << "Current sentence:" RESET<< paragraph.sentences[i].text << endl;;
		cout << RED << "Next sentence:" RESET<< paragraph.sentences[i+1].text << endl;
		cout << "Do you want to merge current sentence with the next sentence? ";
		string response; response = Utils::trim(enterLine());
		if (response == "y" || response == "yes") {
			mergeIdxs.push_back(i);
		}
		clearScreen();
	}

	paragraph.doMerge(mergeIdxs);
	for(auto& s:paragraph.sentences) {
		// cout << s.l <<" " << s.r << endl << endl;

		if (s.isNewlineSentence()) continue;

		while (true) {
			cout << GREEN << "Current sentence:" RESET<< s.text << endl;;
			cout << "Do you want to continue" << RED << " adding new word " << RESET << "in this sentence?(y/yes) ";
			string response; response = Utils::trim(enterLine());
			if (response == "y" || response == "yes") {
				addWord(dictionary, history, setting);
			} else break;
		}

		cout << GREEN << "Current sentence:" RESET<< s.text << endl;;
		cout << RED << "Enter sentence meaning: " << RESET;
		string meaning; meaning = Utils::trim(enterLine());
		s.meaning = meaning;
	}
	collection.add(paragraph);
	history.addParagraph(-1, title);
	collection.save(getCollectionPath(setting.language));
	history.save(getHistoryPath(setting.language));
}

void showParagraph(Paragraph& p) {
	clearScreen();
	ParagraphView pt = ParagraphView(1, 0, Terminal::getWidth() / 2 - 1, p.getText());
	ParagraphView pm = ParagraphView(1, Terminal::getWidth() / 2, Terminal::getWidth() / 2 - 1, p.getMeaning());
	pt.display(); pm.display();
}

void practiceReading(History& history, Collection& collection) {
	cout << "Reading list:" << endl;
	int id = 0;
	for(auto& p:collection.pList) {
		cout << ++id << ". " << p.title << endl;
	}

	int k = enterNumber(1, collection.getSize());
	showParagraph(collection.pList[k - 1]);
}


int main() {

	Dictionary dictionary = Dictionary();
	History history = History();
	Collection collection = Collection();
	Setting setting = Setting(NLAST, LRATE, LANGUAGE);
	loadData(dictionary, history, collection, setting);

	while (true) {
		showMenu();
		int k = enterNumber(1, 6);
		if (k == 1) {
			clearScreen();
			addWord(dictionary, history, setting);
		}
		if (k == 2) {
			learn(dictionary, history, setting);
		}
		if (k == 3) {
			practice(dictionary, history, setting);
		}
		if (k == 4) {
			enterParagraph(dictionary, history, collection, setting);
		}
		if (k == 5) {
			practiceReading(history, collection);
		}
		if (k == 6) {
			changeSetting(dictionary, history, collection, setting);
		}
	}
	return 0;
}