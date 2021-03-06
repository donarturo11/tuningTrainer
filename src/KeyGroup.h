#ifndef KEYGROUP_H
#define KEYGROUP_H
#include <vector>
#include <QDial>
#include <QDoubleSpinBox>
#include <QSettings>
#include <QThread>

#include "MainWindow.h"
#include "globals.h"
#include "semitones.h"
#include "WaveSimple.h"

class QPushButton;

class KeyGroup : public QWidget
{
    Q_OBJECT
    public:
       KeyGroup(int posX, int white, int nId, int keyCode, QSettings *settings, QString settingsKey, QWidget* parent);
       ~KeyGroup();
       QPushButton *m_keyButton;
       QDial *m_tuneDial;
       QLabel *m_Label;
       QDoubleSpinBox *m_spinbox;
       QSettings *m_settings;
       void setLabel(QString text);
       void connectSynth(stk::WaveSimple *synth);
       int getKeyCode();
       int getPosX();
       int getTuneDialPosY();
       int getKeyButtonPosY();
       double getFrequency();
       int getKeyId();
       QString getKeyLabel();
       
    private:
       void setPosX(int posX);
       QString getShortcutString();
       void initKeyButton(int posX, int white, int nId, int keyCode, QWidget* parent);
       void initTuneDial();
       void initLabel();
       void initSpinBox();
       void setConnections();
       void setKeyId(int nId);
       void setKeyCode(int keyCode);
       void setPressedBg();
       void setDefaultBg();
       void setFrequency(double frequency);
       void setFrequencyRange(int min, int max);
       void setTuneDialPosY(int posY);
       void setKeyButtonPosY(int posY);
       void setLabelPosY(int posY);
    protected:
       int mPosX;
       int width, height;
       int keyButtonPosY;
       int tuneDialPosY;
       QWidget *parentClass;
       bool white;
       QString btnStyle;
       QString btnStylePressed;
       QString shortcutString;
       QString keyLabel;
       QString settingsKey;
       int keyCode;
       int keyId;
       double frequency;
       int frequencyMinimal;
       int frequencyMaximal;
       stk::WaveSimple *m_synth;
       bool pressed;
    public slots:
       void pressedSlot();
       void releasedSlot();
       void tuneDialSlot();
       void spinboxSlot();
       void spinboxTextSlot();
       void spinboxEditFinishedSlot();
        
        
};


#endif // KEYGROUP_H
