#pragma once
#include <qabstractitemmodel.h>
#include "Saved_Repository.h"

class myListTabelModel : public QAbstractTableModel
{
private:
	//Saved_Repository& repository;
	Saved_Repository& repository;
public:

	myListTabelModel(Saved_Repository& repo) : repository{ repo } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;

	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


};

