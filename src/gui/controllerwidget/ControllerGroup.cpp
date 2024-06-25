#include "gui/controllerwidget/ControllerGroup.h"
#include <iostream>
namespace GUI {

/* --------------- */
ControllerGroup::ControllerGroup(QWidget* parent) : QWidget(parent)
{}

ControllerGroup::~ControllerGroup()
{
}

void ControllerGroup::createController(bool semitone)
{
    frequency_controllers.push_back(new FrequencyController(semitone, this));
    auto lastController = frequency_controllers.last();
    connect(lastController, &FrequencyController::frequencyChanged, this, &ControllerGroup::onFrequencyChanged);
    lastController->show();
}

void ControllerGroup::onFrequencyChanged(int nr, double frequency)
{
    emit frequencyChanged(nr, frequency);
}

float ControllerGroup::getFrequencyAt(int idx)
{ 
    if (idx < getSize())
        return frequency_controllers[idx]->getFrequency(); 
    else return -1;
}

void ControllerGroup::setFrequencyAt(int idx, float freq)
{
    if (idx < getSize())
        frequency_controllers[idx]->setFrequency(freq);
}

/* --------------- */
} // namespace GUI


