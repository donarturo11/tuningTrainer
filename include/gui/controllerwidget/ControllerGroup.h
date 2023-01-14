#ifndef CONTROLLERGROUP_H
#define CONTROLLERGROUP_H
#include <QWidget>

namespace GUI {

class ControllerGroup : public QWidget
{
Q_OBJECT
public:
    ControllerGroup(QWidget* parent=0);
    ~ControllerGroup();
protected:

};

} // namespace GUI
#endif // CONTROLLERGROUP_H
