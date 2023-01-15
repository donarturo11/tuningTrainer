#include "gui/ControllerWidget.h"
#include <QString>

namespace GUI {

/* ------------ */
ControllerWidget::ControllerWidget(QWidget *parent)
{
    controllerLayout = new QVBoxLayout(this);
    keyboard = new Keyboard(this);
    controls = new ControllerGroup(this);
    label = new QLabel("Press key: " , this);
    controllerLayout->addWidget(controls);
    controllerLayout->addWidget(keyboard);
    controllerLayout->addWidget(label);
    
    connect(keyboard, &Keyboard::noteOn, this, &ControllerWidget::labelPressed);
    connect(keyboard, &Keyboard::noteOff, this, &ControllerWidget::labelReleased);
    
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::labelPressed(int number)
{
    QString s="";
    s="Key number " + QString::number(number) + " pressed";
    label->setText(s);
}

void ControllerWidget::labelReleased(int number)
{
    qDebug() << number << " released";
    QString s="";
    s="Key number " + QString::number(number) + " released";
}

/* ------------ */

} // namespace GUI

