#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED
#include <string>
#include <vector>

class Font {
public:
	bool isDefault;
	int height;
	std::string* c[49];
	std::string path;
	Font(std::string _path, bool _isDefault = true): path(_path), isDefault(_isDefault) {
		load();
	};
	void load();
	std::vector<std::string> getText(std::string text);
	int estimateWidth(std::string text);
	int getHeight();
};

#endif
