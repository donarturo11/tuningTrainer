#include <QApplication>
#include <vector>
#include "window.h"
#include "AudioEngine.h"
#include "WaveSimple.h"
#include "WaveSimpleMixer.h"
#include "globals.h"
//class WaveSimpleMixer;
class AudioEngine;
int main(int argc,  char **argv)
{
	QApplication app(argc, argv);
    Window window;
        
    std::vector <stk::WaveSimple*> synth;
    
	AudioEngine audioengine;
    stk::WaveSimpleMixer mixer;
            
    for (int i=0; i<KEY_NUMBERS; i++) {
        synth.push_back(new stk::WaveSimple);
        synth[i]->loadWave("harpsichord.wav");
        synth[i]->setBaseFrequency(220);
        
        mixer.addInstrument(synth[i]);
        
    }
        
   
    audioengine.connectMixer(&mixer);
    audioengine.init();
    
    window.initKeyboard(&synth);
	window.show();
	return app.exec();
	

}
