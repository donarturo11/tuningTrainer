#include "gui/MainButtons.h"

MainButtons::MainButtons(QWidget *parent) : QWidget(parent)
{
    init();
    connect (m_about_btn, SIGNAL(pressed()), this, SLOT(aboutSlot()));
    connect (m_quit_btn, SIGNAL(pressed()), this, SLOT(quitSlot()));
    connect (m_chooseSample_btn, SIGNAL(pressed()), this, SLOT(chooseSampleSlot()));
    connect (m_reset_btn, SIGNAL(pressed()), this, SLOT(resetSlot()));
    connect (m_clear_btn, SIGNAL(pressed()), this, SLOT(clearSlot()));
}

MainButtons::~MainButtons()
{

}

void MainButtons::init()
{
    int posX=800;
    int posY=0;
    int width=140;
    int height=20;
    
    m_about_btn = new QPushButton("About", this);
    m_quit_btn = new QPushButton("Quit", this);
    m_chooseSample_btn = new QPushButton("Choose sample", this);
    m_reset_btn = new QPushButton("Reset", this);
    m_clear_btn = new QPushButton("Clear config", this);
    
    for (auto button : {m_about_btn, m_quit_btn, m_chooseSample_btn, m_reset_btn, m_clear_btn}) {
        button->setGeometry(posX, posY, width, height);
        button->show();    
        posY+=height;
    }
}

void MainButtons::aboutSlot()
{    
    aboutwindow=new AboutWindow(this);
    aboutwindow->setModal(1);
    aboutwindow->show();
}

void MainButtons::quitSlot()
{
    emit quit();
}

void MainButtons::resetSlot()
{
    //setDefaultFrequencies();
    //setDefaultBaseFrequency();
    //setDefaultWavepath();
    //m_settings->sync();
}

void MainButtons::clearSlot()
{
    resetSlot();
    //m_settings->clear();  
}

void MainButtons::chooseSampleSlot()
{
    choosesamplewindow = new ChooseSampleWindow(this, "");
    choosesamplewindow->setModal(1);
    choosesamplewindow->exec();
#ifdef DEBUG
    qDebug() << "Choosen Sample: " << choosesamplewindow->getWavepath();
    qDebug() << "Base Freq: " << choosesamplewindow->getWavepath();
#endif    
    //this->setWavepath(choosesamplewindow->getWavepath());
    //this->setBaseFreq(choosesamplewindow->getBaseFreq());
    
    //this->loadWave(this->getWavepath());
}    
