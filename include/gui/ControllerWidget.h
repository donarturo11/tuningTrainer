#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H
#include <QWidget>

namespace GUI {
namespace ControllerWidget {    

class ControllerWidget : public QWidget
{
Q_OBJECT    
public:
    ControllerWidget();
    ~ControllerWidget();
signals:
    int noteOn(int number);
    int noteOff(int number);
    int frequencyChanged(int number, int frequency);
};
}
}

#endif // CONTROLLERWIDGET_H
