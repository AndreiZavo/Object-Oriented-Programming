#include "Repository.h"
#include <fstream>

std::vector<TElement> Repository::getElements()
{
	std::vector<TElement> elements;
	std::ifstream fin(this->filename);
	TElement element;
	while (fin >> element) {
		elements.push_back(element);
	}
	fin.close();
	return elements;
}

int Repository::getSize()
{
	return getElements().size();
}


void Repository::setFilename(std::string newFile)
{
	this->filename = newFile;
	std::fstream file;
	file.open(this->filename, std::fstream::in | std::fstream::out | std::fstream::app);
	file.close();
}

int Repository::searchForElementByTitle(const std::string& title)
{
	std::ifstream fin(this->filename);
	TElement element;
	int index = 0;
	while (fin >> element) {
		if (element.getTitle() == title) {
			fin.close();
			return index;
		}
		index++;
	}
	fin.close();
	return -1;
}

int Repository::addElement(const Recording& recording)
{
	int positionOfElement = this->searchForElementByTitle(recording.getTitle());
	if (positionOfElement != -1) {
		return positionOfElement;
	}
	std::ofstream fout(this->filename, std::ios::app);
	fout << recording;
	fout.close();
	return -1;
}

int Repository::UpdateElement(const Recording& recording)
{
	std::ifstream fin(this->filename);
	int index = 0;
	int positionOfElement = -1;
	TElement elementToUpdate;
	std::vector<TElement> elements;

	while (fin >> elementToUpdate) {
		if (elementToUpdate.getTitle() == recording.getTitle()) {
			elementToUpdate.setFilmedAt(recording.getFilmedAt());
			elementToUpdate.setDate(recording.getCreationDate());
			elementToUpdate.setAccessCount(recording.getAccessCount());
			elementToUpdate.setFootagePreview(recording.getFootagePreview());
			positionOfElement = index;
		}
		elements.push_back(elementToUpdate);
		index++;
	}
	fin.close();
	if (positionOfElement == -1) {
		return -1;
	}
	std::ofstream fout(this->filename);
	for (auto& element : elements) {
		fout << element;
	}
	fout.close();
	return positionOfElement;
}

int Repository::removeElement(const std::string& title)
{
	int positionOfelementFound = this->searchForElementByTitle(title);
	if (positionOfelementFound == -1) {
		return -1;
	}
	std::ifstream fin(this->filename);
	TElement current;
	int index = 0;
	int positionOfRemoval = -1;
	std::vector<TElement> elements;
	
	while (fin >> current) {
		if (current.getTitle() != title) {
			elements.push_back(current);
		}
		else {
			positionOfRemoval = index;
		}
		index++;
	}
	fin.close();
	std::ofstream fout(this->filename);
	for (auto& element : elements) {
		fout << element;
	}
	fout.close();
	return positionOfRemoval;
}

Recording Repository::searchForElement(std::string title)
{
	std::ifstream fin(this->filename);
	TElement element;
	int index = 0;
	while (fin >> element) {
		if (element.getTitle() == title) {
			fin.close();
			return element;
		}
		index++;
	}
	fin.close();
	return TElement();
}
