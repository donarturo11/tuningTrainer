#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* --------------- */
FrequencyController::FrequencyController(bool semitone, QWidget* parent) : QWidget(parent)
{
    semitoneKey = semitone;
    init();
    qDebug() << "Created FrequencyController at:" << FrequencyController::index;
    qDebug() << "FrequencyController Geometry: " << geometry();
    FrequencyController::index++;
}

FrequencyController::~FrequencyController()
{
}

void FrequencyController::init()
{
    int pos_y, pos_x;
    m_dial = new QDial(this);
    m_spin = new QDoubleSpinBox(this);
    
    m_spin->setStyleSheet("font-size: 7pt");
    m_spin->setSingleStep(0.1);
    
    pos_x = FrequencyController::position_x;
    pos_x += semitoneKey ? -10 : 10;
    pos_y = semitoneKey ? 0 : 70;
    
    m_dial->setGeometry(0, 0, 50, 50);
    m_spin->setGeometry(0, 50, 50, 20);
    m_spin->show();
    m_dial->show();
    
    setGeometry(pos_x, pos_y, 70, 120);
    FrequencyController::position_x=pos_x;
    
}

/* --------------- */
} // namespace GUI
