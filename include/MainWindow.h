#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QSettings>

#include "gui/MainButtons.h"
#include "keyboard/KeyGroup.h"

#include "globals.h"
#include "semitones.h"

//class QPushButton;
class KeyGroup;
class MainButtons;
class MainWindow : public QWidget
//class MainWindow : public QMainWindow
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
        
        MainButtons *mainButtons;
        KeyGroup* m_keygroup;
        QSettings *m_settings;
    
    public slots:
        
    signals:

	private slots:
        void quitSlot();
        
};


#endif // MAINWINDOW_H
