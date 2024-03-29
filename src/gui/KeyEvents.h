#ifndef KEYEVENTS_H
#define KEYEVENTS_H
#include <QWidget>
#include <QMap>
#include <QVector>
//#include "MainWindow.h"

namespace GUI {

class KeyEvents : public QWidget
{
	Q_OBJECT
public:
    inline static int shortcutIndex = 0;
    KeyEvents(QWidget *parent=0);
	~KeyEvents();
    QString getNameByIndex(int idx) { return keyNames[idx]; }
    int getShortcutIndex(int code) { return keyMap[code]; }
private:
    void addShortcut(int code);
    void addName(int code);
protected:
    QMap<int, int> keyMap; // keyMap[code]=index
    QVector<QString> keyNames;
public slots:
    void sendKeyPressed(int code);
    void sendKeyReleased(int code);
signals:
    void keyPressed(int index);
    void keyReleased(int index);

	//private slots:
        
};
} // namespace GUI

#endif
