#pragma once
#include "Repository.h"
#include "Saved_Repository.h"
#include "Recording.h"
class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() = default;

};

class ActionAdd : public Action {
private:
	Recording addedRecording;
	Repository& repository;

public:
	ActionAdd(Recording recording, Repository& repo);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action {
private:
	Recording deletedRecording;
	Repository& repository;

public:
	ActionRemove(Recording recording, Repository& repo);
	void executeUndo() override;
	void executeRedo() override;

};

class ActionUpdate : public Action {
private:
	Recording oldRecording;
	Recording newRecording;
	Repository& repository;
public:
	ActionUpdate(Recording newRec, Recording oldRec, Repository& repo);
	void executeUndo() override;
	void executeRedo() override;
};

