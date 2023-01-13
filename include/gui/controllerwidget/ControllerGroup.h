#ifndef CONTROLLERGROUP_H
#define CONTROLLERGROUP_H
#include <QWidget>

namespace GUI {

namespace ControllerWidget {

class ControllerGroup : public QWidget
{
Q_OBJECT
public:
    ControllerGroup(QWidget* parent);
    ~ControllerGroup();
protected:

};

} // namespace ControllerWidget

} // namespace GUI
#endif // CONTROLLERGROUP_H
