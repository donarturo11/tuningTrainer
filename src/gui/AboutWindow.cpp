#include "gui/AboutWindow.h"
#include "gui/MainButtons.h"
#include <QString>

AboutWindow::AboutWindow(QWidget *parent) : QDialog(parent)
{
    this->setAboutString();
    this->setWindowTitle("About");
    m_label = new QLabel(this);
    m_label->setTextFormat(Qt::RichText);
    m_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_label->setOpenExternalLinks(true);
    m_label->setText(this->label_str);
    m_label->show();
    
    
}
//-------------------------------------------
void AboutWindow::setAboutString()
{
    QString mailaddress="arturwrona91\x40gmail.com";
    QString mailtoString="mailto:" + mailaddress + "\\?subject=tuningTrainer Support";
    
    label_str+="<h1>TuningTrainer</h1><br>";
    label_str+="by donarturo11<br>";
    label_str+="<a href=\"https://github.com/donarturo11/tuningTrainer\">https://github.com/donarturo11/tuningTrainer</a><br><br>";
    label_str+="TuningTrainer is a small and simple program<br>";
    label_str+="to training tuning systems,<br>";
    label_str+="recommended for<br>";
    label_str+="harpsichordists, organists<br>";
    label_str+="and other who interest in early music.<br>";
    label_str+="<br><br>";
    label_str+="This program uses:<br>";
    label_str+="<b>STK Synthesis Toolkit:</b><br>";
    label_str+="<a href=\"https://ccrma.stanford.edu/software/stk/\">https://ccrma.stanford.edu/software/stk/</a><br><br>";
    label_str+="<b>Realtime Audio:</b><br>";
    label_str+="<a href=\"https://www.music.mcgill.ca/~gary/rtaudio/\">https://www.music.mcgill.ca/~gary/rtaudio/</a><br><br>";
    label_str+="<b>QT5:</b><br>";
    label_str+="<a href=\"https://www.qt.io/\">https://www.qt.io/</a>";
    label_str+="<br><br>";
    label_str+="You can support author by buying him coffee to improve performance of his brain";
    label_str+="<a href=\"https://www.buymeacoffee.com/donarturo11\" target=\"_blank\"><img src=\"https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png\" alt=\"Buy Me A Coffee\" style=\"height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;\" ></a>";
    label_str+="To contact me, please write me at address:<br>";
    label_str+="<a href=\"" + mailtoString + "\">"+mailaddress+"</a><br><br>";
    label_str+="To close this window press &lt;esc&gt;";
    
}
