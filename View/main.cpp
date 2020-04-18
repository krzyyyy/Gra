#include "View.h"
#include <QtWidgets/QApplication>
#include <QTableView>
#include "MyModel.h"
#include "CharacterDelegate.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyModel model;
	QTableView view;
	view.setModel(&model);
	view.show();
	CharacterDelegate my_delegate;
	view.setItemDelegate(&my_delegate);
	view.resizeColumnsToContents();
	view.resizeRowsToContents();
	return a.exec();
}
