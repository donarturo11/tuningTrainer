#include <vector>
#include "globals.h"
/*
#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"
*/
#include <QtGui>
#include <QApplication>
#include <iostream>
#include "MainWindow.h"
#ifdef DEBUG
#define qPrettyDebug() qDebug() << Q_FUNC_INFO
#define qPrettyWarning() qWarning() << Q_FUNC_INFO
#endif

int main(int argc,  char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainwindow;
	mainwindow.show();
    
	return app.exec();
}
