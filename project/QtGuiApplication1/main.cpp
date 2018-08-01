#include "QtGuiPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiPlayer w;
	w.show();
	return a.exec();
}
