#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/ControllerGroup.h"

namespace GUI {

class ControllerWidget : public QWidget
{
Q_OBJECT    
public:
    ControllerWidget(QWidget *parent=0);
    ~ControllerWidget();
public slots:
    void sendNoteOn(int number);   
    void sendNoteOff(int number);
    void sendFrequencyChange(int number, double frequency);
signals:
    void noteOn(int number);
    void noteOff(int number);
    void frequencyChanged(int number, double frequency);
protected:
    Keyboard *keyboard;
    ControllerGroup *controls;
    QLabel *label;
    QVBoxLayout *controllerLayout;
};

}

#endif // CONTROLLERWIDGET_H
