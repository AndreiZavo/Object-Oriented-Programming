#include "myListTabelModel.h"
#include <string>

int myListTabelModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.getSize();
}

int myListTabelModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant myListTabelModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Recording currentRecording = this->repository.getElements()[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(currentRecording.getTitle());
		case 1:
			return QString::fromStdString(currentRecording.getFilmedAt());
		case 2:
			return QString::fromStdString(currentRecording.getCreationDate().toString());
		case 3:
			return QString::number(currentRecording.getAccessCount());
		case 4:
			return QString::fromStdString(currentRecording.getFootagePreview());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant myListTabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section)
			{
			case 0:
				return QString("Title");
			case 1:
				return QString("Filmed at");
			case 2:
				return QString("Creation date");
			case 3:
				return QString("Access count");
			case 4:
				return QString("Footage preview");
			default:
				break;
			}
		}
	}

	return QVariant();
}
