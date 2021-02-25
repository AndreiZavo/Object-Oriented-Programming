#pragma once

#include <QWidget>
#include "ui_myListQtClass.h"
#include "myListTabelModel.h"

class myListQtClass : public QWidget
{
	Q_OBJECT

public:
	myListQtClass(myListTabelModel* model, QWidget *parent = Q_NULLPTR);
	~myListQtClass();

private:
	Ui::myListQtClass ui;
	myListTabelModel* model;
};
