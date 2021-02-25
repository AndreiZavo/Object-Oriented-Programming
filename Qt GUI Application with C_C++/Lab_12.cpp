#include "Lab_12.h"
#include <qmessagebox.h>
#include "myListTabelModel.h"
#include "myListQtClass.h"
#include "qshortcut.h"

Lab_12::Lab_12(Saved_Repository& savedRepo, Service& serv, QWidget *parent)
    : QMainWindow(parent), service(serv), savedRepository(savedRepo)
{
    ui.setupUi(this);
	this->populateList();
	this->makeConnections();
}

void Lab_12::populateList()
{
	this->ui.recordingListWidget->clear();

	std::vector<Recording> allRecordings = this->service.getAllElementsFromFileRepository();
	for (auto record : allRecordings)
		this->ui.recordingListWidget->addItem(QString::fromStdString(record.toString()));
	this->ui.titleLineEdit->clear();
	this->ui.filmedAtLineEdit->clear();
	this->ui.creationDateLineEdit->clear();
	this->ui.accessCountLineEdit->clear();
	this->ui.footagePreviewLineEdit->clear();
}

void Lab_12::makeConnections()
{
	QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);

	QObject::connect(this->ui.deletePushButton, &QPushButton::clicked, this, &Lab_12::deleteRecording);
	QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &Lab_12::addRecording);
	QObject::connect(this->ui.updatePushButton, &QPushButton::clicked, this, &Lab_12::updateRecording);
	QObject::connect(this->ui.filterPushButton, &QPushButton::clicked, this, &Lab_12::filterRecordings);
	QObject::connect(this->ui.modePushButton, &QPushButton::clicked, this, &Lab_12::setMode);
	QObject::connect(this->ui.setRepositoryPushButton, &QPushButton::clicked, this, &Lab_12::setRepository);
	QObject::connect(this->ui.savePushButton, &QPushButton::clicked, this, &Lab_12::saveRecording);
	QObject::connect(this->ui.nextPushButton, &QPushButton::clicked, this, &Lab_12::nextRecording);
	QObject::connect(this->ui.myListPushButton, &QPushButton::clicked, this, &Lab_12::myListRecordings);
	QObject::connect(this->ui.listPushButton, &QPushButton::clicked, this, &Lab_12::listRecordings);
	QObject::connect(this->ui.undoPushButton, &QPushButton::clicked, this, &Lab_12::undo);
	QObject::connect(this->ui.redoPushButton, &QPushButton::clicked, this, &Lab_12::redo);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &Lab_12::undo);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &Lab_12::redo);
}

void Lab_12::setMode()
{
	if (this->service.getAccessMode() == "A") {
		this->service.setAccessMode("B");
		this->ui.currentModeLabel->setText("B");
		this->ui.recordingListWidget->clear();
	}
	else {
		this->service.setAccessMode("A");
		this->ui.currentModeLabel->setText("A");
		this->ui.recordingListWidget->clear();
	}
}

void Lab_12::setRepository()
{
	std::string path = this->ui.setRepositoryLineEdit->text().toStdString();
	this->service.setFileName(path);
	this->populateList();
}

void Lab_12::deleteRecording()
{
	int selectedIndex = this->getSelectedIndex();
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No recording was selecteed!");
		return;
	}

	Recording currentRecording = this->service.getAllElementsFromFileRepository()[selectedIndex];
	this->service.removeElement(currentRecording.getTitle());

	this->populateList();
}

int Lab_12::getSelectedIndex()
{
	QModelIndexList selectedIndexes = this->ui.recordingListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->ui.titleLineEdit->clear();
		this->ui.filmedAtLineEdit->clear();
		this->ui.creationDateLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void Lab_12::addRecording()
{
	std::string title = this->ui.titleLineEdit->text().toStdString();
	std::string filmedAt = this->ui.filmedAtLineEdit->text().toStdString();
	Date creationDate = Date::stringToDate(this->ui.creationDateLineEdit->text().toStdString());
	int accessCount = std::stoi(this->ui.accessCountLineEdit->text().toStdString());
	std::string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();

	this->service.addElement(title, filmedAt, creationDate, accessCount, footagePreview);

	this->populateList();
}

void Lab_12::updateRecording()
{
	std::string title = this->ui.titleLineEdit->text().toStdString();
	std::string filmedAt = this->ui.filmedAtLineEdit->text().toStdString();
	Date creationDate = Date::stringToDate(this->ui.creationDateLineEdit->text().toStdString());
	int accessCount = std::stoi(this->ui.accessCountLineEdit->text().toStdString());
	std::string footagePreview = this->ui.footagePreviewLineEdit->text().toStdString();

	this->service.updateElement(title, filmedAt, creationDate, accessCount, footagePreview);

	this->populateList();
}

void Lab_12::filterRecordings()
{
	this->ui.recordingListWidget->clear();
	std::string filmedAt = this->ui.filmedAtLineEdit->text().toStdString();
	int accessCount = std::stoi(this->ui.accessCountLineEdit->text().toStdString());
	std::vector<Recording> filteredRecordings = this->service.filteredList(filmedAt, accessCount);
	for (auto recording : filteredRecordings) {
		this->ui.recordingListWidget->addItem(QString::fromStdString(recording.toString()));
	}
	this->ui.filmedAtLineEdit->clear();
	this->ui.accessCountLineEdit->clear();
}

void Lab_12::listRecordings()
{
	this->populateList();
	this->populateList();
}

void Lab_12::undo()
{
	this->service.undo();
	this->populateList();
}

void Lab_12::redo()
{
	this->service.redo();
	this->populateList();
}

void Lab_12::saveRecording()
{
	std::string titleToSave = this->ui.titleLineEdit->text().toStdString();
	if (titleToSave != "") {
		this->service.saveElement(titleToSave);
	}
}

void Lab_12::nextRecording()
{
	Recording nextRecording = this->service.next();
	this->ui.currentRecordingListWidget->clear();
	this->ui.currentRecordingListWidget->addItem(QString::fromStdString(nextRecording.toString()));

}

void Lab_12::myListRecordings()
{
	myListTabelModel* model = new myListTabelModel{ this->savedRepository };
	myListQtClass* myList = new myListQtClass{ model };
	myList->show();
}

int Lab_12::getSelectedForSave()
{
	QModelIndexList selectedIndexes = this->ui.currentRecordingListWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.size() == 0) {
		this->ui.titleLineEdit->clear();
		this->ui.filmedAtLineEdit->clear();
		this->ui.creationDateLineEdit->clear();
		this->ui.accessCountLineEdit->clear();
		this->ui.footagePreviewLineEdit->clear();
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}
