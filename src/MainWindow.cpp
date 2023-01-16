#include "MainWindow.h"
#include "gui/load_style.h"
#include <QFile>

//MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
MainWindow::MainWindow() : QMainWindow()
{
    initSettings();
 
    setWindowTitle("TuningTrainer");
    init();
    setFixedSize(800, 300);
    connect (mainButtons, SIGNAL(quit()), this, SLOT(quitSlot()));
    
    m_settings->sync();
    
}

MainWindow::~MainWindow()
{
    m_settings->sync();
}

void MainWindow::init()
{
    
    GUI::load_style(this, ":/qss/main.qss");
	mainButtons = new GUI::MainButtons(this);
    controllerWidget = new GUI::ControllerWidget(this);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(controllerWidget);
    m_layout->addWidget(mainButtons);
    
    mainwidget = new QWidget(this);
    mainwidget->setLayout(m_layout);
    setCentralWidget(mainwidget);
    updateGeometry();
}

void MainWindow::initSettings()
{
    m_settings=new QSettings("donarturo11", "tuningTrainer");
    m_settings->setDefaultFormat(QSettings::IniFormat);
    //appconfiglocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

void MainWindow::quitSlot()
{
    this->close();
}

