#ifndef CONTROLLERGROUP_H
#define CONTROLLERGROUP_H
#include <QWidget>
#include <QVector>
#include "gui/controllerwidget/FrequencyController.h"

namespace GUI {

class ControllerGroup : public QWidget
{
Q_OBJECT
public:
    ControllerGroup(QWidget* parent=0);
    ~ControllerGroup();
    void createController(bool semitone = false);
private:
    
private slots:
    void onFrequencyChanged(int nr, double frequency);
signals:
    void frequencyChanged(int nr, double frequency);
protected:
    QVector<FrequencyController*> frequency_controllers;
};

} // namespace GUI
#endif // CONTROLLERGROUP_H
