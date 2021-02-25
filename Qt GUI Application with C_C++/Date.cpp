#include "Date.h"

std::string Date::toString()
{
	if (this->month < 10 && this->day < 10) 
		return "0" + std::to_string(this->getMonth()) + "-0" + std::to_string(this->getDay()) + "-" + std::to_string(this->getYear());
	else {
		if (this->month < 10 && this->day >= 10) 
			return "0" + std::to_string(this->getMonth()) + "-" + std::to_string(this->getDay()) + "-" + std::to_string(this->getYear());
		else {
			if (this->month >= 10 && this->day < 10) 
				return std::to_string(this->getMonth()) + "-0" + std::to_string(this->getDay()) + "-" + std::to_string(this->getYear());
			else 
				if (this->month >= 10 && this->day >= 10) 
					return std::to_string(this->getMonth()) + "-" + std::to_string(this->getDay()) + "-" + std::to_string(this->getYear());
		}
	}
}

Date Date::stringToDate(const std::string date)
{
	std::string dateElements[4];
	int index = 0;
	for (auto c : date) {
		if (c == '-') {
			index++;
		}
		else {
			dateElements[index] += c;
		}
	}
	int month = std::stoi(dateElements[0]);
	int day = std::stoi(dateElements[1]);
	int year = std::stoi(dateElements[2]);

	return Date(month, day, year);
}
