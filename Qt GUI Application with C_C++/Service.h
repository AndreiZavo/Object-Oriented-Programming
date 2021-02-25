#pragma once
#include "Repository.h"
#include "Saved_Repository.h"
#include "Action.h"

class Service
{
private:

	Repository& fileRepository;
	Saved_Repository& savedRepository;
	std::string accessMode;
	std::vector<Action*> undoRedolist;
	int undoRedoIndex;

public:

	//Constructor
	Service(Repository& fileRepo, Saved_Repository& saveRepo, std::string mode) : fileRepository{ fileRepo }, savedRepository{ saveRepo }, accessMode{ mode } {undoRedolist = std::vector<Action*>(); undoRedoIndex = 0; }

	//Getters

	Repository getFileRepository() { return this->fileRepository; }

	Saved_Repository getSavedRepository() { return this->savedRepository; }

	int getSizeOfSavedRepository() { return this->savedRepository.getSize(); }

	std::vector<TElement> getAllElementsFromFileRepository() const { return this->fileRepository.getElements(); }

	std::vector<TElement> getAllElementsFromSavedRepository() const { return this->savedRepository.getElements(); }

	std::string getAccessMode() { return this->accessMode; }

	//Setter

	int setAccessMode(std::string new_access_mode);

	void setFileName(const std::string& filename);

	//Methods

	int addElement(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int& accessCount, const std::string& footagePreview);

	int updateElement(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int& accessCount, const std::string& footagePreview);

	int removeElement(const std::string& title);

	int saveElement(const std::string& title);

	std::vector<TElement> filteredList(const std::string& filmedAt, const int& maximumAccessCounts);

	TElement next();

	void undo(bool storage = true);

	void redo(bool storage = true);

};

