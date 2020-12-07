#ifndef PARAGRAPHVIEW_H_INCLUDED
#define PARAGRAPHVIEW_H_INCLUDED

#include <string>

struct ParagraphView {
public:
	int x, y, w;
	std::string text;
	ParagraphView(int _x, int _y, int _w, std::string _text): x(_x), y(_y), w(_w), text(_text) {};
	void display();

};
#endif