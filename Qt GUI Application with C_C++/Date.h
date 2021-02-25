#pragma once
#include <string>

class Date
{
private:
	int month;
	int day;
	int year;

public:

	Date() : month(0), day(0), year(0) {}

	Date(const int& _month, const int& _day, const int& _year) : month(_month), day(_day), year(_year) {}

	int getMonth() const { return this->month; }

	int getDay() const { return this->day; }

	int getYear() const { return this->year; }

	std::string toString();

	static Date stringToDate(const std::string date);

};

