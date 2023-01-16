#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QSettings>
#include <QHBoxLayout>

#include "gui/MainButtons.h"
#include "gui/ControllerWidget.h"
#include "gui/KeyEvents.h"

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
        static MainWindow* getMainWindow(){ return MainWindow::mainWindow; }
    private:
        inline static MainWindow* mainWindow=0;
        void init();
        void initSettings();
        void setDefaults();
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        
    protected:
        int waitCount;
        double baseFreq;
        
        GUI::MainButtons *mainButtons;
        GUI::ControllerWidget *controllerWidget;
        QSettings *m_settings;
        QHBoxLayout* m_layout;
        QWidget* mainwidget;
        GUI::KeyEvents *keyEvents; 
    
    public slots:
        
    signals:
        void keyPressed(int keyCode);
        void keyReleased(int keyCode);

	private slots:
        void quitSlot();
        
};


#endif // MAINWINDOW_H
