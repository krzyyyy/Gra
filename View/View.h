#pragma once

#include <QtWidgets/QWidget>
#include "ui_View.h"

class View : public QWidget
{
	Q_OBJECT

public:
	View(QWidget *parent = Q_NULLPTR);

private:
	Ui::ViewClass ui;
};
