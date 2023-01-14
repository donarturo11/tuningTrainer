#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/ControllerGroup.h"

namespace GUI {

class ControllerWidget : public QWidget
{
Q_OBJECT    
public:
    ControllerWidget(QWidget *parent=0);
    ~ControllerWidget();
signals:
    int noteOn(int number);
    int noteOff(int number);
    int frequencyChanged(int number, int frequency);
protected:
    Keyboard *keyboard;
    ControllerGroup *controls;
    QVBoxLayout *controllerLayout;
};

}

#endif // CONTROLLERWIDGET_H
