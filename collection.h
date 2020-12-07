#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#include <vector>
#include <string>
#include "paragraph.h"

#define NEWLINE_TEXT "#########"
class Collection {
public:
	std::vector<Paragraph> pList;
	void load(std::string path);
	void save(std::string path);
	void add(Paragraph paragraph);
	void reset();
	int getSize();
};

#endif