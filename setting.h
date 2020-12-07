
#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED

#include <iostream>
struct Setting {
	int nLast;
	double lRate;
	std::string language;
	Setting(int _nLast, double _lRate, std::string _language): nLast(_nLast), lRate(_lRate), language(_language) {};
	friend std::ostream& operator<<(std::ostream& os, const Setting& setting) {
		os << "nLast: " << setting.nLast << std::endl;
		os << "lRate: " << setting.lRate << std::endl; 
		os << "language: " << setting.language << std::endl; 
		return os;
	}
};
#endif
