#include "MainWindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
//MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initSettings();
 
    setWindowTitle("TuningTrainer");
    init();
    setFixedSize(800, 200);
    connect (mainButtons, SIGNAL(quit()), this, SLOT(quitSlot()));
    
    m_settings->sync();
    
}

MainWindow::~MainWindow()
{
    m_settings->sync();
}

void MainWindow::init()
{
    
    mainButtons = new GUI::MainButtons(this);
    mainButtons->show();
    loadStyle();
}

void MainWindow::initSettings()
{
    m_settings=new QSettings("donarturo11", "tuningTrainer");
    m_settings->setDefaultFormat(QSettings::IniFormat);
    //appconfiglocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

void MainWindow::loadStyle()
{
    QFile mainStyle(":/qss/main.qss");
    mainStyle.open( QFile::ReadOnly );
    QString styleString = QLatin1String(mainStyle.readAll());
    this->setStyleSheet( styleString );
}

void MainWindow::quitSlot()
{
    this->close();
}

