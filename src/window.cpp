#include "window.h"
#include <QString>

Window::Window(QWidget *parent) : QWidget(parent)
{
   // 
    this->waitCount=0;
    
    
    
    
}
//-------------------------------------------
void Window::initKeyboard(std::vector <stk::WaveSimple*> *synth)
{
    
    this->m_synth=synth;
    
    int ind=0;
    int posX=0;
    int color=WHITE;
    
    this->createKey(0, posX, color, ind, Qt::Key_Q); 
    this->createKey(0, posX, color, ind, Qt::Key_W); 
    this->createKey(0, posX, color, ind, Qt::Key_E); 
    this->createKey(KEY_C, posX, color, ind, Qt::Key_R);
    this->createKey(KEY_C_SHARP, posX, color, ind, Qt::Key_5);
    this->createKey(KEY_D, posX, color, ind, Qt::Key_T);
    this->createKey(KEY_D_SHARP, posX, color, ind, Qt::Key_6);
    this->createKey(KEY_E, posX, color, ind, Qt::Key_Y);    
    this->createKey(KEY_F, posX, color, ind, Qt::Key_U);    
    this->createKey(KEY_F_SHARP, posX, color, ind, Qt::Key_8);    
    this->createKey(KEY_G, posX, color, ind, Qt::Key_I);    
    this->createKey(KEY_G_SHARP, posX, color, ind, Qt::Key_9);    
    this->createKey(KEY_A, posX, color, ind, Qt::Key_O);    
    this->createKey(KEY_A_SHARP, posX, color, ind, Qt::Key_0);    
    this->createKey(KEY_B, posX, color, ind, Qt::Key_P);    
    this->createKey(KEY_C_HIGH, posX, color, ind, 91);
    
}

void Window::createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode)
{
    QString keyName=QKeySequence(keyCode).toString();
    myKeyGroup[index]=new KeyGroup(posX, color, index, keyCode, this);
    if (nextSemitone==1 && color==WHITE) {
        posX+=AFTER_WHITE_STEP;
        color=BLACK;
        }
    else if (nextSemitone==1 && color==BLACK) {
        posX+=AFTER_BLACK_STEP;
        color=WHITE;
        }
    else if (nextSemitone==0) {
        posX+=AFTER_BLACK_STEP*3;
        color=WHITE;
        }
        
    this->keyBindMap[keyCode]=index;    
    
    myKeyGroup[index]->setLabel(keyName);
    myKeyGroup[index]->m_tuneDial->setValue(440);
    myKeyGroup[index]->m_spinbox->setValue(440);
    myKeyGroup[index]->connectSynth(m_synth[0][index]);
    
    ++index;
}
//-------------------------------------------
void Window::keyPressEvent(QKeyEvent *event)
{
    
    int keyCode=event->key();
    
    bool autoRepeat=event->isAutoRepeat();
    
    if (this->keyBindMap.find(keyCode)!=this->keyBindMap.end() && !autoRepeat) {
        int objectId=this->keyBindMap[event->key()];
        myKeyGroup[objectId]->pressedSlot();
    }
      
}
//-------------------------------------------
void Window::keyReleaseEvent(QKeyEvent *event)
{
    bool autoRepeat=event->isAutoRepeat();
    
    int keyCode=event->key();
    if (this->keyBindMap.find(keyCode)!=this->keyBindMap.end() && !autoRepeat) {
        int objectId=this->keyBindMap[event->key()];
        myKeyGroup[objectId]->releasedSlot();
        
    }
        
}
