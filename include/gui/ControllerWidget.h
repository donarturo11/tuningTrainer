#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include "MainWindow.h"
#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/ControllerGroup.h"
#include "gui/KeyEvents.h"
#include "synth/Synthesizer.h"

namespace Synth {
    class Synthesizer;
}

class MainWindow;
namespace GUI {

class ControllerWidget : public QWidget
{
Q_OBJECT    
public:
    ControllerWidget(QWidget *parent=0);
    ~ControllerWidget();
    KeyEvents* getKeyEvents() { return _events; }
private:
    void init();
    void setupWidgets();
    void initSynth();
    void connectWidgets();
    void connectEvents();
    void setPolyphony(int voices) { _voices = voices; }
    int getPolyphony() { return _voices; }
public slots:
    void sendNoteOn(int number);   
    void sendNoteOff(int number);
    void sendFrequencyChange(int number, double frequency);
signals:
    void noteOn(int number);
    void noteOff(int number);
    void frequencyChanged(int number, double frequency);
protected:
    //MainWindow *_mainWindow;
    Keyboard *_keyboard;
    ControllerGroup *_controls;
    QVBoxLayout *_controllerLayout;
    KeyEvents *_events;
    Synth::Synthesizer* _synth;
    int _voices;
};

}

#endif // CONTROLLERWIDGET_H
