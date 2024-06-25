#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <thread>
#include "MainWindow.h"
#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/ControllerGroup.h"
#include "gui/KeyEvents.h"
#include "synth/Synthesizer.h"
#include "audio/AudioEngine.h"
#include "gui/WaveLoader.h"

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
    void fillBuffer();
private:
    void init();
    void setupWidgets();
    void initAudio();
    void initSynth();
    void initWaveloader();
    void connectWidgets();
    void connectEvents();
    void loadWave(QString filename, float basefreq = 440);
    void setPolyphony(int voices) { _voices = voices; }
    int getPolyphony() { return _voices; }
public slots:
    void sendNoteOn(int number);   
    void sendNoteOff(int number);
    void sendFrequencyChange(int number, double frequency);
    void loadWaveToSynth(std::vector <float> wave);
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
    AudioEngine* _audio;
    WaveLoader* _waveloader;
    QString _waveFilename;
    float _base_frequency;
    int _voices;
    int _samplerate;
    int _nChannels;
};

}

#endif // CONTROLLERWIDGET_H
