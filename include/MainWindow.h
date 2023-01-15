#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QSettings>
#include <QHBoxLayout>

#include "gui/MainButtons.h"
#include "gui/ControllerWidget.h"

#include "globals.h"
#include "semitones.h"

namespace GUI {
class MainButtons;
}

//class MainWindow : public QWidget
class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow();
		~MainWindow();
    private:
        void init();
        void initSettings();
        void setDefaults();
        
    protected:
        int waitCount;
        double baseFreq;
        
        GUI::MainButtons *mainButtons;
        GUI::ControllerWidget *controllerWidget;
        QSettings *m_settings;
        QHBoxLayout* m_layout;
        QWidget* mainwidget;
    
    public slots:
        
    signals:

	private slots:
        void quitSlot();
        
};


#endif // MAINWINDOW_H
