#include "MainWindow.h"
#include "KeyGroup.h"



KeyGroup::KeyGroup(int posX, int white, int nId, int keyCode, QWidget* parent) //: public QWidget(parent)
{
    this->parentClass=parent;
    
    this->setKeyButtonPosY(150);
    this->setTuneDialPosY(0);
    
    this->initKeyButton(posX, white, nId, keyCode, parent);
    
    this->initTuneDial();
    this->initSpinBox();
    this->setConnections();    
}

//-------------------------------------------

void KeyGroup::initKeyButton(int posX, int white, int nId, int keyCode, QWidget* parent)
{
    int posY=this->getKeyButtonPosY();
    
    this->setKeyId(nId);
    this->setPosX(posX);
    QString textAlignStr;
    QString keyLabel=this->getKeyLabel();
    QString keyName=QKeySequence(keyCode).toString();
    
    
    textAlignStr="text-align: bottom; font-size: 30px";
    
    
    if (white==WHITE) {
        btnStyle="background-color: #ffffff; color: #000000; ";
        btnStyle+=textAlignStr;
        btnStylePressed="background-color: #c0c0c0; color: #101010; ";
        btnStylePressed+=textAlignStr;
        width=WHITE_KEY_WIDTH;
        height=WHITE_KEY_HEIGHT;
        
     }
     
     else {
         btnStyle="background-color: #000000; color: #ffffff; ";
         btnStyle+=textAlignStr;
         btnStylePressed="background-color: #404040; color: #c0c0c0; ";
         btnStylePressed+=textAlignStr;
         width=BLACK_KEY_WIDTH;
         height=BLACK_KEY_HEIGHT;
         }
    
    this->white=white;
    
    m_keyButton = new QPushButton("[]", parent);
    m_keyButton->setAutoFillBackground("true");
    m_keyButton->setStyleSheet(btnStyle);
    m_keyButton->setGeometry(posX, posY, width , height);
    m_keyButton->setText(keyName);
    if (white) m_keyButton->lower();
    else m_keyButton->raise();
    
    m_keyButton->show();
}
//-------------------------------------------
void KeyGroup::initTuneDial() 
{
        
    int posX, posY, width, height;
    posY=this->getTuneDialPosY();
    posX=this->getPosX();
    
    posY+=20;
    
    if (this->white==WHITE) posY+=60;
    if (this->white==BLACK) posX-=10;
    //else posY+=0;
    width=50;
    height=50;
    m_tuneDial = new QDial(parentClass);
    m_tuneDial->setGeometry(posX, posY, width, height);
    m_tuneDial->setWrapping(false);
    m_tuneDial->setMinimum(220);
    m_tuneDial->setMaximum(880);
    m_tuneDial->show();
    
    connect (m_tuneDial, SIGNAL(valueChanged(int)), this, SLOT(tuneDialSlot()));

}
//-------------------------------------------
void KeyGroup::initSpinBox() 
{
    int posX, posY, width, height;
    posY=this->getTuneDialPosY();
    posX=this->getPosX();
    posY+=5;
    if (this->white==WHITE) posY+=60;
    //if (this->white==BLACK) posX-=10;
    //else posY+=0;
    width=50;
    height=20;
    
    m_spinbox = new QSpinBox(parentClass);
    
    
    m_spinbox->setGeometry(posX, posY, width, height);
    m_spinbox->setWrapping(false);
    m_spinbox->setMinimum(220);
    m_spinbox->setMaximum(880);
    m_spinbox->show();
    
    connect (m_spinbox, SIGNAL(valueChanged(int)), this, SLOT(spinboxSlot()));
}
//-------------------------------------------

//-------------------------------------------
void KeyGroup::initLabel() 
{
    
}
//-------------------------------------------
void KeyGroup::tuneDialSlot()
{
    int value = m_tuneDial->value();
    m_spinbox->setValue(value);
    this->setFrequency(value);
    
    
}
//-------------------------------------------
void KeyGroup::spinboxSlot()
{
    int value = m_spinbox->value();
    m_tuneDial->setValue(value);
    this->setFrequency(value);
    this->parentClass->setFocus();
    
    
}
//-------------------------------------------
void KeyGroup::setPressedBg()
{
    m_keyButton->setStyleSheet(btnStylePressed);
}
//-------------------------------------------
void KeyGroup::setDefaultBg()
{
    m_keyButton->setStyleSheet(this->btnStyle);
}
//-------------------------------------------
void KeyGroup::setKeyId(int nId)
{
     this->keyId=nId;   
}
//-------------------------------------------
int KeyGroup::getKeyId()
{
    return this->keyId;
}
//-------------------------------------------
void KeyGroup::setKeyCode(int keyCode)
{
     this->keyCode=keyCode;   
}
//-------------------------------------------
void KeyGroup::setLabel(QString text)
{
    this->keyLabel=text;
}
//-------------------------------------------
QString KeyGroup::getKeyLabel()
{
    return this->keyLabel;
}
//-------------------------------------------
void KeyGroup::setPosX(int posX)
{
    this->mPosX=posX;
}
//-------------------------------------------
void KeyGroup::setKeyButtonPosY(int posY) 
{
    this->keyButtonPosY=posY;
}
//-------------------------------------------
int KeyGroup::getKeyButtonPosY()
{
    return this->keyButtonPosY;   
}
//-------------------------------------------
void KeyGroup::setTuneDialPosY(int posY) 
{
    this->tuneDialPosY=posY;
}
//-------------------------------------------
int KeyGroup::getTuneDialPosY()
{
    return this->tuneDialPosY;   
}
//-------------------------------------------
int KeyGroup::getPosX()
{
    return this->mPosX;
}
//-------------------------------------------
int KeyGroup::getKeyCode()
{
     return this->keyCode;   
}

//-------------------------------------------
int KeyGroup::getFrequency()
{
    return this->frequency;
}
//-------------------------------------------
void KeyGroup::setFrequency(int frequency)
{
    this->frequency=frequency;
    m_synth->setFrequency(frequency);
    
}
//-------------------------------------------

void KeyGroup::setConnections() 
{
    connect(
             m_keyButton, 
             SIGNAL (pressed() ), 
             this, 
             SLOT( pressedSlot() ) 
           );
    
    connect(
             m_keyButton, 
             SIGNAL (released() ), 
             this, 
             SLOT( releasedSlot() ) 
           );
}
//-------------------------------------------
void KeyGroup::pressedSlot() 
{
    int id=this->getKeyId();
    int freq=this->getFrequency();
    this->setPressedBg();
    
    m_synth->noteOn(freq, 0.3);
    
}
//-------------------------------------------
void KeyGroup::releasedSlot() 
{
    this->setDefaultBg();
    m_synth->noteOff(0.0);
}
//-------------------------------------------


void KeyGroup::connectSynth(stk::WaveSimple* synth)
{
    
    this->m_synth = synth;
    
}



