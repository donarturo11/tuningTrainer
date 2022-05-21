#include "ChooseSampleWindow.h"
#include <QString>

ChooseSampleWindow::ChooseSampleWindow(QWidget *parent) : QDialog(parent)
{
    this->setString();
    this->setWindowTitle("Choose sample window");
    m_label = new QLabel(label_str, this);
    m_label->show();
    
    
}
//-------------------------------------------
void ChooseSampleWindow::setString()
{
    label_str+="Choose sample";
}
