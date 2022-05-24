#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
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
#include "ChooseSampleWindow.h"
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
        ChooseSampleWindow *choosesamplewindow;
        QSettings *m_settings;
        void initKeyboard(std::vector <stk::WaveSimple*> *synth);
        void setWavepath(QString path);
        QString getWavepath();
        void loadWave(QString path);
        
	private:
        
        KeyGroup *myKeyGroup[KEY_NUMBERS];
        QPushButton *m_about_btn;
        QPushButton *m_chooseSample_btn;
        QPushButton *m_quit_btn;
        QPushButton *m_reset_btn;
        QString wavepath="";
        std::map<int, int> keyBindMap;
        void createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode, QSettings *settings);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        std::vector <stk::WaveSimple*> *m_synth;
        
        
        
    protected:
        int waitCount;
    
    public slots:
        void aboutSlot();
        void chooseSampleSlot();
        void resetSlot();
        void quitSlot();
        
    signals:
        void noteOn(int value);
        void noteOff();
    
        
	//private slots:
        
};


#endif // MAINWINDOW_H
