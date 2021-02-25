#pragma once
#include <string>
#include "Date.h"
#include <vector>

class Recording
{
private:
	std::string title;
	std::string filmedAt;
	Date creationDate;
	int accessCount;
	std::string footagePreview;

public:

	Recording() : title(""), filmedAt(""), creationDate(Date()), accessCount(0), footagePreview("") {}
	
	Recording(const std::string& _title, const std::string& _filmedAt, const Date& date, const int& count, const std::string& footagePrev);

	std::string getTitle() const { return this->title; }

	std::string getFilmedAt() const { return this->filmedAt; }

	Date getCreationDate() const { return this->creationDate; }

	int getAccessCount() const { return this->accessCount; }

	std::string getFootagePreview() const { return this->footagePreview; }

	void setTitle(std::string newTitle) { this->title = newTitle; }

	void setFilmedAt(std::string newFilm) { this->filmedAt = newFilm; }

	void setDate(Date newDate) { this->creationDate = newDate; }

	void setAccessCount(int newAccessCount) { this->accessCount = newAccessCount; }

	void setFootagePreview(std::string newFootagePreview) { this->footagePreview = newFootagePreview; }

	std::string toString();

	friend std::vector<std::string> tokensize(const std::string& string, char delimiter);

	friend std::istream& operator>>(std::istream& is, Recording& recording);

	friend std::ostream& operator<<(std::ostream& os, const Recording& recording);
	
};

