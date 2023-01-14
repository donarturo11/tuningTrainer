#include "gui/MainButtons.h"
#include "gui/AboutWindow.h"
#include "gui/ChooseSampleWindow.h"

namespace GUI {
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
    int posX=0;
    int posY=0;
    int width=140;
    int height=20;
    
    m_about_btn = new QPushButton("About", this);
    m_quit_btn = new QPushButton("Quit", this);
    m_chooseSample_btn = new QPushButton("Choose sample", this);
    m_reset_btn = new QPushButton("Reset", this);
    m_clear_btn = new QPushButton("Clear config", this);
    
    m_buttons_layout = new QVBoxLayout(this);
    m_buttons_layout->setSpacing(0);
    
    for (auto button : {m_about_btn, m_quit_btn, m_chooseSample_btn, m_reset_btn, m_clear_btn}) {
        m_buttons_layout->addWidget(button);
    }
}

void MainButtons::aboutSlot()
{    
    AboutWindow aboutwindow(this);
    aboutwindow.setModal(1);
    aboutwindow.exec();
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
    ChooseSampleWindow choosesamplewindow(this, "");
    choosesamplewindow.setModal(1);
    choosesamplewindow.exec();
}

} //namespace GUI