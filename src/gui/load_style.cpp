#include "gui/load_style.h"
#include <QFile>
namespace GUI {
void load_style(QWidget* w, QString filename)
{
QFile style_qss(filename);
style_qss.open( QFile::ReadOnly );
QString styleString = QLatin1String(style_qss.readAll());
w->setStyleSheet( styleString );
}
}