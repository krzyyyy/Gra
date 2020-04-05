#include "View.h"
#include <QtWidgets/QApplication>
#include <QTableView>
#include "MyModel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyModel model;
	QTableView view;
	view.setModel(&model);
	view.show();
	View w;
	w.show();
	return a.exec();
}
