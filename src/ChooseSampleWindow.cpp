#include "ChooseSampleWindow.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>

ChooseSampleWindow::ChooseSampleWindow(QWidget *parent, QString wavepath) : QDialog(parent)
{
    this->setString();
    this->setWindowTitle("Choose sample window");
    this->wavepath = wavepath;
    
    //m_label = new QLabel(label_str, this);
    //m_label->show();
        
    init();
    
    
}
//-------------------------------------------
void ChooseSampleWindow::init(){
    
    m_browse_btn = new QPushButton("Browse", this);
    m_browse_btn->setGeometry(605, 0, 60, 30);
    m_browse_btn->show();
    connect (m_browse_btn, SIGNAL(pressed()), this, SLOT(browseSlot()));
    
    m_waveurl = new QLineEdit(getWavepath(), this);
    m_waveurl->setGeometry(0, 0, 600, 30);
    m_waveurl->setFocus();
    m_waveurl->show();
    
    m_apply_btn = new QPushButton("Apply", this);
    m_apply_btn->setGeometry(0, 30, 60, 30);
    m_apply_btn->setDefault(true);
    m_apply_btn->show();
    connect (m_apply_btn, SIGNAL(pressed()), this, SLOT(applySlot()));
    
    m_cancel_btn = new QPushButton("Cancel", this);
    m_cancel_btn->setGeometry(70, 30, 60, 30);
    m_cancel_btn->show();
    connect (m_cancel_btn, SIGNAL(pressed()), this, SLOT(quitSlot()));
    
    m_baseFreq_label = new QLabel("Frequency of source sample:", this);
    m_baseFreq_label->setGeometry(200, 30, 200, 30);
    //m_baseFreq_label->show();
    
    m_baseFreq_spin = new QSpinBox(this);
    m_baseFreq_spin->setGeometry(400, 30, 60, 30);
    m_baseFreq_spin->setRange(30, 880);
    m_baseFreq_spin->setValue(220);
    //m_baseFreq_spin->show();
}


void ChooseSampleWindow::setString()
{
    label_str+="Choose sample";
}

QString ChooseSampleWindow::getWavepath()
{
    return this->wavepath;
}

void ChooseSampleWindow::setWavepath(QString path)
{
    this->wavepath=path;
}

void ChooseSampleWindow::browseSlot()
{
    QString wavepath = QFileDialog::getOpenFileName(m_waveurl, "Browse wave", this->wavepath, tr("Wave file (*.wav)"));
    m_waveurl->setText(wavepath);
    qDebug() << "End browse slot: " << this->wavepath;
}

void ChooseSampleWindow::applySlot()
{
    this->wavepath = m_waveurl->text();
    this->close();
}

void ChooseSampleWindow::quitSlot()
{
    this->close();
}
