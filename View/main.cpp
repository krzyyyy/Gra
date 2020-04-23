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
	CharacterDelegate my_delegate;
	view.setItemDelegate(&my_delegate);
	view.resizeColumnsToContents();
	view.resizeRowsToContents();
	view.setGeometry(50, 50 , view.sizeHint().width()+500, view.sizeHint().height()+500);
	view.show();
	return a.exec();
}
