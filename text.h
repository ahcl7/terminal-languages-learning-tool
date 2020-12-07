#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "font.h"
#include <string>
#define CENTER 0
#define LEFT 1
#define RIGHT 2


const std::string DEFAULT_FONT_PATH = "default.font";

class Text {
public:
	Font font;
	int align;
	std::string text;
	int y;

	Text(): font(Font(DEFAULT_FONT_PATH)) {};
	Text(std::string _text, Font _font, int _align, int _y): text(_text), font(_font), align(_align), y(_y){}; 
	void setFont(Font _font) {
		font = _font;
	}

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
