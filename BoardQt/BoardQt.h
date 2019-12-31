#pragma once

#include <QtWidgets/QMainWindow>
//#include "ui_BoardQt.h"
#include "ui_BoardQt.h"

class BoardQt : public QMainWindow
{
	Q_OBJECT

public:
	BoardQt(QWidget *parent = Q_NULLPTR);

private:
	Ui::BoardQtClass ui;
};
