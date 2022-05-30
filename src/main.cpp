#include <vector>
#include "globals.h"

#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"
#include <QtGui>
#include <QApplication>
#include <QDebug>
#include "MainWindow.h"

int main(int argc,  char **argv)
{
    stk::Stk::showWarnings( false );
    stk::Stk::printErrors( false );

    std::vector <stk::WaveSimple*> synth;
    
    AudioEngine audioengine;
    stk::WaveSimpleMixer mixer;
    
    //qDebug() << "Vector synth address: " << &synth;
            
    for (int i=0; i<KEY_NUMBERS; i++) {
        synth.push_back(new stk::WaveSimple);
        //synth[i]->loadWave("harpsichord.wav");
        synth[i]->setBaseFrequency(220);
        mixer.addInstrument(synth[i]);
        //qDebug() << "Main | Synth[" << i << "]=" << synth[i];
    }

    audioengine.connectMixer(&mixer);
    audioengine.init();

    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.initKeyboard(&synth);
	mainwindow.show();
	return app.exec();
}
