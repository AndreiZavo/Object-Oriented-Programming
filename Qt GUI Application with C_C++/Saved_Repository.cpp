#include "Saved_Repository.h"
#include <fstream>

std::vector<TElement> Saved_Repository::loadFromFile(int& numberOfElements)
{
	std::ifstream fin(this->filename);
	std::vector<TElement> elements;
	TElement element;
	numberOfElements = 0;
	while (fin >> element) {
		elements.push_back(element);
		numberOfElements++;
	}
	fin.close();
	return elements;
}

Saved_Repository::Saved_Repository(std::string filename)
{
	this->filename = filename;
	this->current = 0;
}

TElement Saved_Repository::getCurrent()
{
	std::vector<TElement> elements;
	int numberOfElements;
	elements = this->loadFromFile(numberOfElements);
	return elements[this->current];

}

void Saved_Repository::saveElement(const TElement& element)
{
	if (this->searchElementByTitle(element.getTitle()) == -1)
		this->elements.push_back(element);
}

void Saved_Repository::nextElement()
{
	std::vector<TElement> elements;
	int numberOfElements;
	elements = this->loadFromFile(numberOfElements);
	if (this->current == numberOfElements - 1) {
		this->begin();
	}
	else {
		this->current++;
	}
}

void Saved_Repository::begin()
{
	this->current = 0;
}

int Saved_Repository::searchElementByTitle(const std::string& title)
{	
	int index = 0;
	for (auto recording : this->elements) {
		if (recording.getTitle() == title) {
			return index;
		}
		index++;
	}
	return -1;
}

