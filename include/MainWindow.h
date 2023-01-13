#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QSettings>

#include "gui/MainButtons.h"

#include "globals.h"
#include "semitones.h"

namespace GUI {
class MainButtons;
}

class MainWindow : public QWidget
{
	Q_OBJECT
	public:
		MainWindow(QWidget *parent=0);
		~MainWindow();
    private:
        void init();
        void initSettings();
        void loadStyle();
        void setDefaults();
        
    protected:
        int waitCount;
        double baseFreq;
        
        GUI::MainButtons *mainButtons;
        QSettings *m_settings;
    
    public slots:
        
    signals:

	private slots:
        void quitSlot();
        
};


#endif // MAINWINDOW_H