#include "gui/ControllerWidget.h"

#include <QString>
#include <QDebug>

#include "gui/controllerwidget/KeyButton.h"
#include "gui/KeyEvents.h"
#include "gui/controllerwidget/FrequencyController.h"
#include "gui/WaveLoader.h"

namespace GUI {

/* ------------ */
ControllerWidget::ControllerWidget(QWidget *parent) : QWidget(parent)
{
    init();
    setupWidgets();
    connectWidgets();
    connectEvents();
    initSynth();
    initAudio();
    
    setFixedSize(FrequencyController::position_x+100, 400);
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::init()
{
    _samplerate = 44100;
    _events = new KeyEvents(this);
    _controllerLayout = new QVBoxLayout(this);
    _keyboard = new Keyboard(this);
    _controls = new ControllerGroup(this);
}

void ControllerWidget::setupWidgets()
{
    int voices = 0;
    
    _controllerLayout->addWidget(_controls);
    _controllerLayout->addWidget(_keyboard);
    
    for (bool black : {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0}) {
        _keyboard->initKey(black);
        FrequencyController::position_x=_keyboard->getKeyLast()->getX();
        _controls->createController(black);
        voices++;
    }
    
    setPolyphony(voices);
}

void ControllerWidget::connectWidgets()
{
    connect(_keyboard, &Keyboard::noteOn, this, &ControllerWidget::sendNoteOn);
    connect(_keyboard, &Keyboard::noteOff, this, &ControllerWidget::sendNoteOff);
    connect(_controls, &ControllerGroup::frequencyChanged, this, &ControllerWidget::sendFrequencyChange);
}

void ControllerWidget::connectEvents()
{
    connect(parentWidget(), SIGNAL(keyPressed(int)), _events, SLOT(sendKeyPressed(int)));
    connect(parentWidget(), SIGNAL(keyReleased(int)), _events, SLOT(sendKeyReleased(int)));
    
    connect(_events, &KeyEvents::keyPressed, _keyboard, &Keyboard::setButtonPressed);
    connect(_events, &KeyEvents::keyReleased, _keyboard, &Keyboard::setButtonReleased);
}

void ControllerWidget::initAudio()
{
    _audio = new AudioEngine();
    _audio->setSamplerate(_samplerate);
    _audio->connectSource(_synth);
    _audio->startStream();
}

void ControllerWidget::initSynth()
{
    int voices = getPolyphony();
    _synth = new Synth::Synthesizer(voices);
    loadWave(":/resources/harpsichord.wav");
}

void ControllerWidget::sendNoteOn(int number)
{
    //qDebug() << number << " pressed";
    _synth->sendNoteOn(number);
}

void ControllerWidget::sendNoteOff(int number)
{
    //qDebug() << number << " released";
    _synth->sendNoteOff(number);
}

void ControllerWidget::sendFrequencyChange(int number, double frequency)
{
    //qDebug() << "Synth number " << number << " has frequency " << frequency << "Hz";
    _synth->sendFrequencyChange(number, frequency);
    setFocus();
}

void ControllerWidget::loadWave(QString filename)
{
    if (!_synth) return;
    WaveLoader loader(this, _samplerate, _nChannels);
    
    connect(&loader, &WaveLoader::sendWave, this, &ControllerWidget::loadWaveToSynth);
    loader.load(filename);
}

void ControllerWidget::loadWaveToSynth(std::vector <float> wave)
{
    _synth->loadWave(wave);
}

/* ------------ */

} // namespace GUI

