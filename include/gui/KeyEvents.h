#ifndef KEYEVENTS_H
#define KEYEVENTS_H
#include <QWidget>
#include <QShortcut>
#include <QKeyEvent>
//#include "MainWindow.h"

namespace GUI {

class KeyEvents : public QWidget
{
	Q_OBJECT
public:
	KeyEvents(QWidget *parent=0);
	~KeyEvents();
    void sendKeyPressed(int code);
    void sendKeyReleased(int code);
private:
    
protected:
    QShortcut* shortcut;
public slots:
    
public slots:

signals:


	//private slots:
        
};
} // namespace GUI

#endif
