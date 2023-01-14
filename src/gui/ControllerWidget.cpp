#include "gui/ControllerWidget.h"
namespace GUI {

/* ------------ */
ControllerWidget::ControllerWidget(QWidget *parent)
{
    controllerLayout = new QVBoxLayout(this);
    keyboard = new Keyboard(this);
    controls = new ControllerGroup(this);
    controllerLayout->addWidget(keyboard);
    controllerLayout->addWidget(controls);
}

ControllerWidget::~ControllerWidget()
{

}

/* ------------ */

} // namespace GUI