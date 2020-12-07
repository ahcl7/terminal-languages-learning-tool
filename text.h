#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <string>
#define CENTER 0
#define LEFT 1
#define RIGHT 2



class Text {
public:
	int align;
	std::string text;
	int y;

	Text(std::string _text, int _align, int _y): text(_text), align(_align), y(_y){};

	void setAlign(int _align) {
		align = _align;
	}

	void setText(std::string _text) {
		text = _text;
	}

	void setY(int _y) {
		y = _y;
	}
	void display();

	int getX();
	int estimateHeight();

	void highlight(std::string pattern, std::string style);
protected:
	std::vector<std::string> getSegments();
	void displaySegment(std::string, int padding = 0);
	int getX(std::string text);
	std::string pattern;
	std::string style;
};

#endif
