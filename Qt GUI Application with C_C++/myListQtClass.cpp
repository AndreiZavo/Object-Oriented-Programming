#include "myListQtClass.h"

myListQtClass::myListQtClass(myListTabelModel* model, QWidget *parent)
	: QWidget(parent), model{ model }
{
	ui.setupUi(this);

	ui.myListTableView->setModel(this->model);
}

myListQtClass::~myListQtClass()
{
}
