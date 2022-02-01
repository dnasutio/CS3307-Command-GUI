#include "mainwindow.h"
#include "CommandClass.h"
#include <QApplication>

/*
 * Dylan Nasution
 * CS3307A
 */

int main(int argc, char *argv[])
{
	// opens GUI
	QApplication app(argc, argv);
  	CommandGUI mainWindow;
  	mainWindow.showNormal();
  	return app.exec();
}
