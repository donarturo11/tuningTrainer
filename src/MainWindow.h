#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#ifndef __APPLE__
#include <QApplication>
#endif
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QKeySequence>
#include <QSettings>
#include <QShortcut>
#include <QKeyEvent>
#include <QThread>
#include <map>
#include <vector>

#include "AboutWindow.h"
#include "KeyGroup.h"
#include "globals.h"
#include "semitones.h"

#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"

//class QPushButton;
class KeyGroup;

class MainWindow : public QWidget
//class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		explicit MainWindow(QWidget *parent=0);
		~MainWindow();
        AboutWindow *aboutwindow;
        QSettings *m_settings;
        void initKeyboard(std::vector <stk::WaveSimple*> *synth);
        
	private:
        
        KeyGroup *myKeyGroup[KEY_NUMBERS];
        QPushButton *m_about_btn;
        QPushButton *m_quit_btn;
        QPushButton *m_reset_btn;
        std::map<int, int> keyBindMap;
        void createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode, QSettings *settings);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        
        std::vector <stk::WaveSimple*> *m_synth;
        
        
        
    protected:
        int waitCount;
    
    public slots:
        void aboutSlot();
        void resetSlot();
        void quitSlot();
        
    signals:
        void noteOn(int value);
        void noteOff();
    
        
	//private slots:
        
};


#endif // MAINWINDOW_H
