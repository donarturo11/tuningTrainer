#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* --------------- */
FrequencyController::FrequencyController(bool semitone, QWidget* parent) : QWidget(parent)
{
    semitoneKey = semitone;
    init();
    qDebug() << "Created FrequencyController at:" << FrequencyController::index;
    qDebug() << "Geomoetry: " << geometry();
    FrequencyController::index++;
}

FrequencyController::~FrequencyController()
{
}

void FrequencyController::init()
{
    int pos_x, pos_y;
    m_dial = new QDial(this);
    m_spin = new QDoubleSpinBox(this);
    
    m_spin->setStyleSheet("font-size: 7pt");
    m_spin->setSingleStep(0.1);
    
    pos_x = FrequencyController::position_x;
    pos_y = semitoneKey ? 0 : 30;
    //setGeometry(pos_x, pos_y, 10, 60);
    //setGeometry(pos_x, pos_y, 70, 120);
    m_dial->setGeometry(0, pos_y, 50, 50);
    m_spin->setGeometry(0, 80, 50, 20);
    m_spin->show();
    m_dial->show();
    //m_layout = new QVBoxLayout(this);
    //m_layout->addWidget(m_dial);
    //m_layout->addWidget(m_spin);
    setGeometry(pos_x, 30, 70, 120);
    
    pos_x += 50;
    FrequencyController::position_x=pos_x;
}

/* --------------- */
} // namespace GUI
