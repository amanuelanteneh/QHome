#include "qHome.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[]){
	QApplication a(argc, argv);

	qHome theApp;

	QDesktopWidget desktop;
	int screenHeight = desktop.geometry().height();
	int screenWidth = desktop.geometry().width();

	theApp.setFixedSize(screenWidth/2.6, screenWidth/2.6);

	theApp.show(); 

	return(a.exec());
}




