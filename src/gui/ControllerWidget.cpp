#include "gui/load_style.h"
#include "gui/ControllerWidget.h"
#include <QString>
#include <QDebug>

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
    
    for (bool black : {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0}) {
        qDebug() << "============";
        keyboard->initKey(black);
        controls->createController(black);
        qDebug() << "============";
    }
    GUI::load_style(this, ":/qss/keyboard.qss");
    connect(keyboard, &Keyboard::noteOn, this, &ControllerWidget::labelPressed);
    connect(keyboard, &Keyboard::noteOff, this, &ControllerWidget::labelReleased);
    
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::labelPressed(int number)
{
    qDebug() << number << " pressed";
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

