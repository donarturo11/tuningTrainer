#include "gui/controllerwidget/ControllerGroup.h"

namespace GUI {

/* --------------- */
ControllerGroup::ControllerGroup(QWidget* parent) : QWidget(parent)
{
    qDebug() << "Controller group c-tor";
    
}

ControllerGroup::~ControllerGroup()
{
}

void ControllerGroup::createController(bool semitone)
{
    frequency_controllers.push_back(new FrequencyController(semitone, this));
    frequency_controllers.last()->show();
}

void ControllerGroup::onFrequencyChanged(int nr, double frequency)
{
    
}

/* --------------- */
} // namespace GUI


