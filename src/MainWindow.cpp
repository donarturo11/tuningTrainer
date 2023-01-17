#include "MainWindow.h"
#include "gui/load_style.h"
#include <QFile>

//MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
MainWindow::MainWindow() : QMainWindow()
{
    MainWindow::mainWindow = this;
    initSettings();
 
    setWindowTitle("TuningTrainer");
    init();
    connect (_mainButtons, SIGNAL(quit()), this, SLOT(quitSlot()));
    
    _settings->sync();
    
}

MainWindow::~MainWindow()
{
    _settings->sync();
}

void MainWindow::init()
{
    
    GUI::load_style(this, ":/qss/main.qss");
	_mainButtons = new GUI::MainButtons(this);
    _controllerWidget = new GUI::ControllerWidget(this);

    _layout = new QHBoxLayout(this);
    _layout->addWidget(_controllerWidget);
    _layout->addWidget(_mainButtons);
    
    _mainwidget = new QWidget(this);
    _mainwidget->setLayout(_layout);
    setCentralWidget(_mainwidget);
    updateGeometry();
}

void MainWindow::initSettings()
{
    _settings=new QSettings("donarturo11", "tuningTrainer");
    _settings->setDefaultFormat(QSettings::IniFormat);
    //appconfiglocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

void MainWindow::quitSlot()
{
    this->close();
}



void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if (!event->isAutoRepeat()) {
        emit keyPressed(event->key());
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
    if (!event->isAutoRepeat()) {
        emit keyReleased(event->key());
    }   
}