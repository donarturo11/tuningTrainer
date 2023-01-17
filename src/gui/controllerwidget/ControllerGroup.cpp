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
    auto lastController = frequency_controllers.last();
    connect(lastController, &FrequencyController::frequencyChanged, this, &ControllerGroup::onFrequencyChanged);
    lastController->show();
}

void ControllerGroup::onFrequencyChanged(int nr, double frequency)
{
    emit frequencyChanged(nr, frequency);
}

/* --------------- */
} // namespace GUI


