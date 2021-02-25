#include "Service.h"
#include <exception>


int Service::setAccessMode(std::string new_access_mode)
{
	if (!(new_access_mode == "A" || new_access_mode == "B")) {
		return false;
	}
	this->accessMode = new_access_mode;
	return true;
}

void Service::setFileName(const std::string& filename)
{
	this->fileRepository.setFilename(filename);
	this->savedRepository.setFilename(filename);
}

int Service::addElement(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int& accessCount, const std::string& footagePreview)
{
	if (this->accessMode != "A") {
		return -8;
	}
	Recording record_to_add{ title, filmedAt, creationDate, accessCount, footagePreview };
	int resultOfAddition = this->fileRepository.addElement(record_to_add);
	this->undoRedolist.resize(undoRedoIndex);
	undoRedolist.push_back(new ActionAdd(record_to_add, this->fileRepository));
	undoRedoIndex++;
	return resultOfAddition;
}

int Service::updateElement(const std::string& title, const std::string& filmedAt, const Date& creationDate, const int& accessCount, const std::string& footagePreview)
{
	if (this->accessMode != "A") {
		return -8;
	}
	Recording recording_to_update = this->fileRepository.searchForElement(title);
	Recording recordingUpdated{ title, filmedAt, creationDate, accessCount, footagePreview };
	int resultOfUpdate = this->fileRepository.UpdateElement(recordingUpdated);
	this->undoRedolist.resize(undoRedoIndex);
	this->undoRedolist.push_back(new ActionUpdate(recordingUpdated, recording_to_update, this->fileRepository));
	undoRedoIndex++;
	return resultOfUpdate;
}

int Service::removeElement(const std::string& title)
{
	if (this->accessMode != "A") {
		return -8;
	}
	Recording recordingToDelete = this->fileRepository.searchForElement(title);
	int resultOfRemoval = this->fileRepository.removeElement(title);
	this->undoRedolist.resize(undoRedoIndex);
	this->undoRedolist.push_back(new ActionRemove(recordingToDelete, this->fileRepository));
	undoRedoIndex++;
	return resultOfRemoval;
}

int Service::saveElement(const std::string& title)
{
	if (this->accessMode != "B") {
		return -8;
	}
	TElement element;
	int positionOfElementToSave = this->fileRepository.searchForElementByTitle(title);
	if (positionOfElementToSave == -1) {
		return -1;
	}
	element = this->fileRepository.getElements()[positionOfElementToSave];
	this->savedRepository.saveElement(element);
	return positionOfElementToSave;
}

std::vector<TElement> Service::filteredList(const std::string& filmedAt, const int& maximumAccessCounts)
{
	std::vector<TElement> allRecordings = this->getAllElementsFromFileRepository();
	std::vector<TElement> filteredRecordings;
	for (auto recording : allRecordings) {
		if (recording.getFilmedAt() == filmedAt && recording.getAccessCount() < maximumAccessCounts) {
			filteredRecordings.push_back(recording);
		}
	}
	return filteredRecordings;
}

TElement Service::next()
{
	if (this->accessMode != "B") {
		return TElement();
	}
	TElement element = this->savedRepository.getCurrent();
	this->savedRepository.nextElement();
	return element;
}

void Service::undo(bool storage)
{
	if (storage) {
		if (undoRedoIndex == 0) {
			throw ("No more undos");
		}
		undoRedolist[--undoRedoIndex]->executeUndo();
	}
}

void Service::redo(bool storage)
{
	if (storage) {
		if (undoRedoIndex == undoRedolist.size()) {
			throw ("No more redos");
		}
		undoRedolist[undoRedoIndex++]->executeRedo();
	}
}
