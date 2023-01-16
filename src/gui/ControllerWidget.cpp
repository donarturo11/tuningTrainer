#include "gui/ControllerWidget.h"
#include <QString>
#include <QDebug>
#include "gui/controllerwidget/KeyButton.h"
#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* ------------ */
ControllerWidget::ControllerWidget(QWidget *parent)
{
    controllerLayout = new QVBoxLayout(this);
    keyboard = new Keyboard(this);
    controls = new ControllerGroup(this);
    controllerLayout->addWidget(controls);
    controllerLayout->addWidget(keyboard);
    
    for (bool black : {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0}) {
        qDebug() << "============";
        keyboard->initKey(black);
        FrequencyController::position_x=keyboard->getKeyLast()->getX();
        controls->createController(black);
        qDebug() << "============";
    }
    
    connect(keyboard, &Keyboard::noteOn, this, &ControllerWidget::sendNoteOn);
    connect(keyboard, &Keyboard::noteOff, this, &ControllerWidget::sendNoteOff);
    setFixedSize(FrequencyController::position_x+100, 400);
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::sendNoteOn(int number)
{
    qDebug() << number << " pressed";
    QString s="";
    s="Key number " + QString::number(number) + " pressed";
    label->setText(s);
}

void ControllerWidget::sendNoteOff(int number)
{
    qDebug() << number << " released";
    QString s="";
    s="Key number " + QString::number(number) + " released";
}

void ControllerWidget::sendFrequencyChange(int number, double frequency)
{
    
}

/* ------------ */

} // namespace GUI

