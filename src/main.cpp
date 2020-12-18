#include "qHome.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	qHome theApp;

	QDesktopWidget desktop;
	int screenHeight = desktop.geometry().height();
	int screenWidth = desktop.geometry().width();

	theApp.setFixedSize(screenWidth/3, screenWidth/3);

	theApp.show(); 

	return(a.exec());
}




