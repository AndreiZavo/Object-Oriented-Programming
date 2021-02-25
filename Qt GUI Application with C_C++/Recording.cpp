#include "Recording.h"
#include <fstream>
#include <sstream>


Recording::Recording(const std::string& _title, const std::string& _filmedAt, const Date& date, const int& count, const std::string& footagePrev)
{
	this->title = _title;
	this->filmedAt = _filmedAt;
	this->creationDate = date;
	this->accessCount = count;
	this->footagePreview = footagePrev;
}

std::string Recording::toString()
{
	return "Title: " + this->getTitle() + "\n\tFilmed at: " + this->getFilmedAt() + "\n\tCreation date: " + this->getCreationDate().toString() + "\n\tAccess Count: " + std::to_string(this->getAccessCount()) + "\n\tFootage Preview: " + this->getFootagePreview() + '\n';
}

std::vector<std::string> tokensize(const std::string& string, char delimiter)
{
	std::vector<std::string> result;
	std::string token;
	std::stringstream stringStream(string);
	while (getline(stringStream, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}

std::istream& operator>>(std::istream& is, Recording& recording)
{
	std::string line;
	getline(is, line);

	std::vector<std::string> tokens = tokensize(line, ',');
	if (tokens.size() != 5) {
		return is;
	}
	recording.setTitle(tokens[0]);
	recording.setFilmedAt(tokens[1]);
	recording.setDate(Date::stringToDate(tokens[2]));
	recording.setAccessCount(std::stoi(tokens[3]));
	recording.setFootagePreview(tokens[4]);

	return is;

}

std::ostream& operator<<(std::ostream& os, Recording& recording)
{
	os << recording.getTitle() << "," << recording.getFilmedAt() << "," << recording.getCreationDate().toString() << "," << std::to_string(recording.getAccessCount()) << "," << recording.getFootagePreview() << "\n";
	return os;
}
