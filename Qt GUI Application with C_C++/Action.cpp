#include "Action.h"

ActionAdd::ActionAdd(Recording recording, Repository& repo) : addedRecording(std::move(recording)) , repository(repo) {}

void ActionAdd::executeUndo()
{
	this->repository.removeElement(addedRecording.getTitle());
}

void ActionAdd::executeRedo()
{
	this->repository.addElement(addedRecording);
}

ActionRemove::ActionRemove(Recording recording, Repository& repo) : deletedRecording(recording), repository(repo) {}

void ActionRemove::executeUndo()
{
	this->repository.addElement(deletedRecording);
}

void ActionRemove::executeRedo()
{
	this->repository.removeElement(deletedRecording.getTitle());
}

ActionUpdate::ActionUpdate(Recording newRec, Recording oldRec, Repository& repo): newRecording(newRec), oldRecording(oldRec), repository(repo) {}

void ActionUpdate::executeUndo()
{
	this->repository.UpdateElement(oldRecording);
}

void ActionUpdate::executeRedo()
{
	this->repository.UpdateElement(newRecording);
}
