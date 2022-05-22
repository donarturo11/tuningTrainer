#include "ChooseSampleWindow.h"
#include <QString>

ChooseSampleWindow::ChooseSampleWindow(QWidget *parent) : QDialog(parent)
{
    this->setString();
    this->setWindowTitle("Choose sample window");
    //m_label = new QLabel(label_str, this);
    //m_label->show();
    init();
    
    
}
//-------------------------------------------
void ChooseSampleWindow::init(){
    m_waveurl = new QLineEdit(this);
    m_waveurl->setGeometry(0, 0, 600, 30);
    m_waveurl->show();
    
    m_browse_btn = new QPushButton("Browse", this);
    m_browse_btn->setGeometry(605, 0, 60, 30);
    m_browse_btn->show();
    connect (m_browse_btn, SIGNAL(pressed()), this, SLOT());
    
    m_apply_btn = new QPushButton("Apply", this);
    m_apply_btn->setGeometry(0, 30, 60, 30);
    m_apply_btn->show();
    connect (m_apply_btn, SIGNAL(pressed()), this, SLOT());
    
    m_cancel_btn = new QPushButton("Cancel", this);
    m_cancel_btn->setGeometry(70, 30, 60, 30);
    m_cancel_btn->show();
    connect (m_cancel_btn, SIGNAL(pressed()), this, SLOT(quitSlot()));
}


void ChooseSampleWindow::setString()
{
    label_str+="Choose sample";
}


void ChooseSampleWindow::quitSlot()
{
    this->close();
}
