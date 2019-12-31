#include "BoardQt.h"

BoardQt::BoardQt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//connect(ui.pb_wyjscie, SIGNAL(clicked()), this, SLOT(exit()));
}
//void BoardQt::exit() {
//	QApplication::exit();
//}