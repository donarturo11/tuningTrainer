#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* --------------- */
FrequencyController::FrequencyController(bool semitone, QWidget* parent)
{
    qDebug() << "Created FrequencyController at:" << FrequencyController::index;
    FrequencyController::index++;
}

FrequencyController::~FrequencyController()
{
}

/* --------------- */
} // namespace GUI
