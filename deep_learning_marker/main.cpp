#include "ui/MainWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

	a.setStyleSheet("QWidget{background:black;}");

	w.show();
	return a.exec();
}