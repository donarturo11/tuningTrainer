#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
//MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   // 
    qDebug() << "MainWindow Constructor:" << this;
    m_settings=new QSettings("donarturo11", "tuningTrainer");
    m_settings->setDefaultFormat(QSettings::IniFormat);
    
    this->appconfiglocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    qDebug() << this->appconfiglocation;
    
    qDebug() << "samplePath=" << m_settings->value("samplePath", "").toString();
    
    this->wavepath = m_settings->value("samplePath", "").toString();
    this->setWindowTitle("TuningTrainer");
    this->waitCount=0;
    
    int posX=800;
    int posY=0;
    int width=140;
    int height=20;
    
    findWave();
    
    m_about_btn = new QPushButton("About", this);
    m_about_btn->setGeometry(posX, posY, width, height);
    m_about_btn->show();
    connect (m_about_btn, SIGNAL(pressed()), this, SLOT(aboutSlot()));
    
    posY+=height;
    
    m_quit_btn = new QPushButton("Quit", this);
    m_quit_btn->setGeometry(posX, posY, width, height);
    m_quit_btn->show();
    connect (m_quit_btn, SIGNAL(pressed()), this, SLOT(quitSlot()));
    
    posY+=height*2;
    
    m_chooseSample_btn = new QPushButton("Choose sample", this);
    m_chooseSample_btn->setGeometry(posX, posY, width, height);
    m_chooseSample_btn->show();
    connect (m_chooseSample_btn, SIGNAL(pressed()), this, SLOT(chooseSampleSlot()));
    
    posY+=height;
    
    m_reset_btn = new QPushButton("Reset", this);
    m_reset_btn->setGeometry(posX, posY, width, height);
    m_reset_btn->show();
    connect (m_reset_btn, SIGNAL(pressed()), this, SLOT(resetSlot()));
    
    
    
    
}

MainWindow::~MainWindow()
{
    m_settings->sync();
}
//-------------------------------------------
void MainWindow::findWave()
{
    QStringList searchPaths;
    QStringList foundPaths;
    QString filename="harpsichord.wav";
    QString fullpath="";
    searchPaths << ".";
    searchPaths << QCoreApplication::applicationDirPath();
    searchPaths << this->appconfiglocation;
    //searchPaths << QStandardPaths::writableLocation();
    
    #if !defined(__OS_WINDOWS__) && !defined(__APPLE__) 
    searchPaths << "/usr/share/tuningTrainer"
                << "/usr/local/share/tuningTrainer";
    #elif(__APPLE__) 
    searchPaths << "/Applications/tuningTrainer.app/MacOS/Resources";
    #endif
    
    searchPaths << QDir::currentPath();
    
    
    for(int i=0; i<searchPaths.size(); i++){
        fullpath = searchPaths.at(i) + "/";
        foundPaths << searchPath(fullpath, filename);
        //qDebug() << fullpath << QFile::exists(fullpath);
    }
    
    for(int i=0; i<foundPaths.size(); i++){
        qDebug() << "Found: " << foundPaths.at(i);
    }
    
}

QStringList MainWindow::searchPath(QString dir, QString filename)
{
    QStringList foundPath;
    QDirIterator it(dir, QDirIterator::Subdirectories);
    QString path;
    while (it.hasNext()){
        path = it.next();
        if (path.contains(filename)){
            foundPath << path;
        }
    }
    return foundPath;
}


void MainWindow::initKeyboard(std::vector <stk::WaveSimple*> *synth)
{
    
    this->m_synth=synth;
    
    int ind=0;
    int posX=0;
    int color=WHITE;
    
    this->createKey(0, posX, color, ind, Qt::Key_Q, m_settings); 
    this->createKey(0, posX, color, ind, Qt::Key_W, m_settings); 
    this->createKey(0, posX, color, ind, Qt::Key_E, m_settings); 
    this->createKey(KEY_C, posX, color, ind, Qt::Key_R, m_settings);
    this->createKey(KEY_C_SHARP, posX, color, ind, Qt::Key_5, m_settings);
    this->createKey(KEY_D, posX, color, ind, Qt::Key_T, m_settings);
    this->createKey(KEY_D_SHARP, posX, color, ind, Qt::Key_6, m_settings);
    this->createKey(KEY_E, posX, color, ind, Qt::Key_Y, m_settings);    
    this->createKey(KEY_F, posX, color, ind, Qt::Key_U, m_settings);    
    this->createKey(KEY_F_SHARP, posX, color, ind, Qt::Key_8, m_settings);    
    this->createKey(KEY_G, posX, color, ind, Qt::Key_I, m_settings);    
    this->createKey(KEY_G_SHARP, posX, color, ind, Qt::Key_9, m_settings);    
    this->createKey(KEY_A, posX, color, ind, Qt::Key_O, m_settings);    
    this->createKey(KEY_A_SHARP, posX, color, ind, Qt::Key_0, m_settings);    
    this->createKey(KEY_B, posX, color, ind, Qt::Key_P, m_settings);    
    this->createKey(KEY_C_HIGH, posX, color, ind, 91, m_settings);
    
}

void MainWindow::createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode, QSettings *settings)
{
    QString keyName=QKeySequence(keyCode).toString();
    //------------
    QString settingsKey="keyID";
    if (index < 10) settingsKey+="0";
    settingsKey+=QString::number(index);
    //--------------
    myKeyGroup[index]=new KeyGroup(posX, color, index, keyCode, m_settings, settingsKey, this);
    if (nextSemitone==1 && color==WHITE) {
        posX+=AFTER_WHITE_STEP;
        color=BLACK;
        }
    else if (nextSemitone==1 && color==BLACK) {
        posX+=AFTER_BLACK_STEP;
        color=WHITE;
        }
    else if (nextSemitone==0) {
        posX+=AFTER_BLACK_STEP*3;
        color=WHITE;
        }
        
    this->keyBindMap[keyCode]=index;    
    
    myKeyGroup[index]->setLabel(keyName);
    myKeyGroup[index]->connectSynth(m_synth[0][index]);
    //myKeyGroup[index]->m_tuneDial->setValue(440);
    //myKeyGroup[index]->m_spinbox->setValue(440);
    
    
    
    ++index;
}
//-------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    
    int keyCode=event->key();
    
    bool autoRepeat=event->isAutoRepeat();
    
    if (this->keyBindMap.find(keyCode)!=this->keyBindMap.end() && !autoRepeat) {
        int objectId=this->keyBindMap[event->key()];
        myKeyGroup[objectId]->pressedSlot();
    }
      
}
//-------------------------------------------
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    bool autoRepeat=event->isAutoRepeat();
    
    int keyCode=event->key();
    if (this->keyBindMap.find(keyCode)!=this->keyBindMap.end() && !autoRepeat) {
        int objectId=this->keyBindMap[event->key()];
        myKeyGroup[objectId]->releasedSlot();
        
    }
        
}

void MainWindow::chooseSampleSlot()
{
    choosesamplewindow = new ChooseSampleWindow(this);
    choosesamplewindow->setModal(1);
    choosesamplewindow->exec();
    this->setWavepath(choosesamplewindow->getWavepath());
    
    this->loadWave(this->getWavepath());
    
    qDebug() << "End function";
}

void MainWindow::loadWave(QString path){
    qDebug() << "Main window | WavePath = " << path;
    qDebug() << "Main window | Good: " << this->m_synth[0][0]->isGood();
    for (int i=0; i<KEY_NUMBERS; i++)
    {
        this->m_synth[0][i]->loadWave(path.toStdString());
    }
    
    m_settings->setValue("samplePath", path);
    qDebug() << "samplePath=" << m_settings->value("samplePath", "").toString();
}

void MainWindow::setWavepath(QString path)
{
    this->wavepath=path;
}

QString MainWindow::getWavepath(){
    return this->wavepath;
}

void MainWindow::aboutSlot()
{
    
    aboutwindow=new AboutWindow(this);
    aboutwindow->setModal(1);
    aboutwindow->show();
    
}

void MainWindow::quitSlot()
{
    this->close();
}

void MainWindow::resetSlot()
{
    for (int i=0; i<KEY_NUMBERS; i++)
    {
        myKeyGroup[i]->m_spinbox->setValue(440);
    }
    m_settings->clear();
}
