#pragma once
#include "Recording.h"
#include <vector>

typedef Recording TElement;

class Repository
{
private:
	std::vector<TElement> recordings;
	std::string filename;
public:

	Repository(const std::string& file) : filename(file) {}

	std::vector<TElement> getElements();

	int getSize();

	void setFilename(std::string newFile);

	/*
	input: title - string
	output: returns the position of the element if the element is found and -1 if not
	*/
	int searchForElementByTitle(const std::string& title);

	/*
	input: recording - Recording
	output: returns -1 if the element was successfully added and the position of the element if it already exists;
	*/
	int addElement(const Recording& recording);
	
	/*
	input: recording - Recording
	output: returns the position if the element was successfully updated and -1 if the element doesn't exist; 
	*/
	int UpdateElement(const Recording& recording);

	/*
	input: title - string
	output: returns -1 if the element is not existent and the position if it was removed successfully
	*/
	int removeElement(const std::string& title);

	Recording searchForElement(std::string title);
};