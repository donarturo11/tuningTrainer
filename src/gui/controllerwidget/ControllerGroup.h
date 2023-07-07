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
    float getFrequencyAt(int idx);
    void setFrequencyAt(int idx, float freq);
    int getSize() { return frequency_controllers.size(); }
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
