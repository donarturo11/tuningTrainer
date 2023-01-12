#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <vector>
#include <thread>


#include "globals.h"
#include "rtaudio/RtAudio.h"
#include "stk/Stk.h"
#include "WaveSimpleMixer.h"
#include "WaveSimple.h"
namespace stk {
class WaveSimpleMixer;
}
class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();
    
    std::vector <stk::WaveSimple*> *m_synth;
    stk::WaveSimpleMixer *m_mixer;
    
    void start();
    void stop();
    void init();
    void setRunning(bool running);  
    void setAudioValue(stk::StkFloat value);
    void connectMixer(stk::WaveSimpleMixer *synth);
    
private:
    void probeSampleRate();
    
    

protected:
    RtAudio *output;
    bool running;
    stk::StkFloat audioValue;
    stk::StkFloat buffer_[1024];

};



#endif // SYNTH_H
