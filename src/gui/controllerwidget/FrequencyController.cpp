#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

/* --------------- */
FrequencyController::FrequencyController(bool semitone, QWidget* parent) : QWidget(parent)
{
    semitoneKey = semitone;
    _index = FrequencyController::index;
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
    m_spin->setGeometry(0, 50, 60, 20);
    m_spin->show();
    m_dial->show();
    
    connect(m_dial, 
            &QDial::valueChanged, 
            this, 
            &FrequencyController::onDialValueChanged);
            
    connect(m_spin, 
            &QDoubleSpinBox::valueChanged, 
            this, 
            &FrequencyController::onSpinValueChanged);
    
    connect(this,
            &FrequencyController::frequencyChanged,
            this,
            &FrequencyController::changeFrequency);
            
    m_dial->setMaximum(freq_max);
    m_dial->setMinimum(freq_min);
    m_spin->setMaximum(freq_max);
    m_spin->setMinimum(freq_min);
    setGeometry(pos_x, pos_y, 70, 120);
    FrequencyController::position_x=pos_x;
    
}

void FrequencyController::onSpinValueChanged(double value)
{
    int idx = getIndex();
    m_dial->setValue((int) value);
    emit frequencyChanged(idx, value);
}

void FrequencyController::onDialValueChanged(int value)
{
    m_spin->setValue((double) value);
}
void FrequencyController::changeFrequency(int index, double frequency)
{
}

/* --------------- */
} // namespace GUI
