#include "BoardQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BoardQt w;
	w.show();
	return a.exec();
}
