#include "AboutWindow.h"
#include <QString>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent)
{
    this->setAboutString();
    this->setWindowTitle("About");
    m_label = new QLabel(label_str, this);
    m_label->show();
    
    
}
//-------------------------------------------
void AboutWindow::setAboutString()
{
    label_str+="TuningTrainer\n";
    label_str+="by donarturo11\n";
    label_str+="\n";
    label_str+="TuningTrainer is a small and simple program\n";
    label_str+="to training tuning systems,\n";
    label_str+="recommended for\n";
    label_str+="harpsichordists, organists\n";
    label_str+="and other who interest in early music.\n";
    label_str+="\n\n";
    label_str+="This program uses:\n";
    label_str+="STK Synthesis Toolkit:\n https://ccrma.stanford.edu/software/stk/ \n\n";
    label_str+="Realtime Audio:\n https://www.music.mcgill.ca/~gary/rtaudio/ \n\n";
    label_str+="QT5:\n https://www.qt.io/ \n\n";
    label_str+="\n\n";
    label_str+="To contact me, please write at address\n";
    label_str+="arturwrona91(at)gmail(dot)com\n";
}
