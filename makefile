english: utils.h utils.cpp cons.h setting.h paragraph.h paragraph.cpp paragraphview.h paragraphview.cpp collection.h collection.cpp history.h history.cpp evaluate.h evaluate.cpp font.h font.cpp text.h text.cpp rd.h rd.cpp temp.h temp.cpp timemanager.h timemanager.cpp word.h word.cpp dictionary.h dictionary.cpp main.cpp
	g++ -o english utils.cpp paragraph.cpp collection.cpp history.cpp paragraphview.cpp evaluate.cpp font.cpp text.cpp timemanager.cpp rd.cpp temp.cpp word.cpp dictionary.cpp main.cpp -std=c++11 -w
clean: rm english
