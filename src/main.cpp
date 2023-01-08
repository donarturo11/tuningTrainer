#include <vector>
#include "globals.h"

#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"
#include <QtGui>
#include <QApplication>
#include <QDebug>
#include "MainWindow.h"
#ifdef DEBUG
#define qPrettyDebug() qDebug() << Q_FUNC_INFO
#define qPrettyWarning() qWarning() << Q_FUNC_INFO
#endif

int main(int argc,  char **argv)
{
#ifdef DEBUG
    fprintf(stderr, "tuningTrainer - Debug mode");
    qSetMessagePattern("%{function} | %{message}");
#endif
#ifdef _STK_DEBUG_
    stk::Stk::showWarnings( true );
    stk::Stk::printErrors( true );
#else
    stk::Stk::showWarnings( false );
    stk::Stk::printErrors( false );
#endif

    std::vector <stk::WaveSimple*> synth;
    
    AudioEngine audioengine;
    stk::WaveSimpleMixer mixer;
    
    for (int i=0; i<KEY_NUMBERS; i++) {
        synth.push_back(new stk::WaveSimple);
        synth[i]->setBaseFrequency(220);
        mixer.addInstrument(synth[i]);
    }

    audioengine.connectMixer(&mixer);
    audioengine.init();

    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.initKeyboard(&synth);
	mainwindow.show();
	return app.exec();
}
