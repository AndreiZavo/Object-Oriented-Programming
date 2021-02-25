#pragma once
#include "Recording.h"

typedef Recording TElement;


class Saved_Repository
{
private:
	std::vector<TElement> elements;
	std::string filename;
	int current;

	std::vector<TElement> loadFromFile(int& numberOfElements);

public:
	//Constructor
	Saved_Repository(std::string filename);

	//Getters

	std::vector<TElement> getElements() { return this->elements; }

	std::string getFilename() { return this->filename; }

	int getSize() { return this->elements.size(); }

	TElement getCurrent();

	//Setter

	void setFilename(const std::string new_filename) { this->filename = new_filename; }

	//Methods

	void saveElement(const TElement& element);

	void nextElement();

	void begin();

	int searchElementByTitle(const std::string& title);
};

