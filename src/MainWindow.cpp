#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
//MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_settings=new QSettings("donarturo11", "tuningTrainer");
    m_settings->setDefaultFormat(QSettings::IniFormat);
    this->appconfiglocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
 
    this->setWindowTitle("TuningTrainer");
    this->waitCount=0;
    init(); //temp
    
    connect (mainButtons, SIGNAL(quit()), this, SLOT(quitSlot()));
    
    m_settings->sync();
    
}

MainWindow::~MainWindow()
{
    m_settings->sync();
}

void MainWindow::init()
{
    mainButtons = new MainButtons(this);
    mainButtons->show();
    
    
}

void MainWindow::quitSlot()
{
    this->close();
}

void MainWindow::initKeyboard(std::vector <stk::WaveSimple*> *synth)
{
 /*   
    this->m_synth=synth;
    
    this->baseFreq = m_settings->value("baseFreq", 220).toDouble();
    this->wavepath = m_settings->value("samplePath", findDefaultWavePath()).toString();
    if(QFile::exists(this->wavepath)) {
        this->wavepath=findDefaultWavePath();
        m_settings->setValue("samplePath", this->wavepath);
        this->loadWave(this->wavepath);
    } 

    int ind=0;
    int posX=0;
    int color=WHITE;
    //this->createKey args: keyLetter, X offset, color (white=1/black=0), KEYCODE, QSettings
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
    */ 
    
}

void MainWindow::createKey(int nextSemitone, int &posX, int &color, int &index, int keyCode, QSettings *settings)
{
    /*
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
    */ 
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


void MainWindow::setBaseFreq(double freq)
{
    this->baseFreq=freq;
    for (int i=0; i<KEY_NUMBERS; i++)
    {
        this->m_synth[0][i]->setBaseFrequency(freq);
    }
    m_settings->setValue("baseFreq", freq);
}

double MainWindow::getBaseFreq()
{
    return this->baseFreq;
}

void MainWindow::loadWave(QString path){
    for (int i=0; i<KEY_NUMBERS; i++)
    {
        this->m_synth[0][i]->loadWave(path.toStdString());
    }
    m_settings->setValue("samplePath", path);
}

void MainWindow::setWavepath(QString path)
{
    this->wavepath=path;
}

QString MainWindow::getWavepath()
{
    return this->wavepath;
}

  

void MainWindow::setDefaultFrequencies()
{
    for (int i=0; i<KEY_NUMBERS; i++)
    {
        myKeyGroup[i]->m_spinbox->setValue(440);
    }
}

void MainWindow::setDefaultBaseFrequency()
{
    setBaseFreq(220);
}
/*
void MainWindow::setDefaultWavepath()
{
    //setWavepath(findDefaultWavePath());
#ifdef DEBUG
    qDebug() << "WavePath: " << this->wavepath;
#endif
}
*/
