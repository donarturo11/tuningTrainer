#include "gui/ChooseSampleWindow.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>

ChooseSampleWindow::ChooseSampleWindow(QWidget *parent, QString wavepath) : QDialog(parent)
{
    this->setString();
    this->setWindowTitle("Choose sample window");
    this->wavepath = wavepath;
    
    this->parentClass=parent;

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
    m_baseFreq_label->show();
    
    m_baseFreq_spin = new QDoubleSpinBox(this);
    m_baseFreq_spin->setGeometry(400, 30, 60, 30);
    m_baseFreq_spin->setRange(FREQ_MIN, FREQ_MAX);
    m_baseFreq_spin->setValue(220);
    connect (m_baseFreq_spin, SIGNAL(valueChanged(double)), this, SLOT(baseFreqSlot()));
    m_baseFreq_spin->show();
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

void ChooseSampleWindow::baseFreqSlot()
{
    double value = m_baseFreq_spin->value();
    this->setBaseFreq(value);
}

void ChooseSampleWindow::browseSlot()
{
    QString wavepath = QFileDialog::getOpenFileName(m_waveurl, "Browse wave", this->wavepath, tr("Wave file (*.wav)"));
    m_waveurl->setText(wavepath);
#ifdef DEBUG
    qDebug() << "End browse slot: " << this->wavepath;
#endif
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

double ChooseSampleWindow::getBaseFreq()
{
    return this->baseFreq;
}

void ChooseSampleWindow::setBaseFreq(double freq)
{
    this->baseFreq=freq;
#ifdef DEBUG
    qDebug() << "Base frequency: " << getBaseFreq();
#endif
}


