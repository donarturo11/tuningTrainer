#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QKeySequence>
#include <QShortcut>
#include <QKeyEvent>
#include <QThread>
#include <iostream>
#include <map>
#include <vector>


#include "keygroup.h"
#include "globals.h"
#include "semitones.h"


#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"

//class QPushButton;
class KeyGroup;

class Window : public QWidget
{
	Q_OBJECT
	public:
		explicit Window(QWidget *parent=0);
        void initKeyboard(std::vector <stk::WaveSimple*> *synth);
                
	private:
        
        KeyGroup *myKeyGroup[KEY_NUMBERS];
        std::map<int, int> keyBindMap;
        void createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode);
        void keyPressEvent(QKeyEvent *event);
        void keyReleaseEvent(QKeyEvent *event);
        
        std::vector <stk::WaveSimple*> *m_synth;
        
        
        
    protected:
        int waitCount;
        
    signals:
        void noteOn(int value);
        void noteOff();
    
        
	//private slots:
        
};


#endif // WINDOW_H
