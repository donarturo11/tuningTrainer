#include "gui/ControllerWidget.h"

#include <QString>
#include <QDebug>

#include "gui/controllerwidget/KeyButton.h"
#include "gui/KeyEvents.h"
#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* ------------ */
ControllerWidget::ControllerWidget(QWidget *parent) : QWidget(parent)
{
    MainWindow* _mainWindow = MainWindow::getMainWindow();
    _controllerLayout = new QVBoxLayout(this);
    _keyboard = new Keyboard(this);
    _controls = new ControllerGroup(this);
    _events = new KeyEvents(this);
    
    _controllerLayout->addWidget(_controls);
    _controllerLayout->addWidget(_keyboard);
    
    for (bool black : {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0}) {
        qDebug() << "============";
        _keyboard->initKey(black);
        FrequencyController::position_x=_keyboard->getKeyLast()->getX();
        _controls->createController(black);
        qDebug() << "============";
    }
    
    connect(_keyboard, &Keyboard::noteOn, this, &ControllerWidget::sendNoteOn);
    connect(_keyboard, &Keyboard::noteOff, this, &ControllerWidget::sendNoteOff);
    connect(_mainWindow, &MainWindow::keyPressed, _events, &KeyEvents::sendKeyPressed);
    connect(_mainWindow, &MainWindow::keyReleased, _events, &KeyEvents::sendKeyReleased);
    connect(_controls, &ControllerGroup::frequencyChanged, this, &ControllerWidget::sendFrequencyChange);
    setFixedSize(FrequencyController::position_x+100, 400);
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::sendNoteOn(int number)
{
    qDebug() << number << " pressed";
}

void ControllerWidget::sendNoteOff(int number)
{
    qDebug() << number << " released";
}

void ControllerWidget::sendFrequencyChange(int number, double frequency)
{
    qDebug() << "Synth number " << number << " has frequency " << frequency << "Hz";
    setFocus();
}

/* ------------ */

} // namespace GUI

