#ifndef VOICE_H
#define VOICE_H
#include "synth/common.h"
#include "synth/Synthesizer.h"
#include "synth/WaveLoop.h"
#include "stk/LentPitShift.h"
namespace Synth {
class Synthesizer;
class Voice
{
public:
    inline static int index=0;
    Voice(Synthesizer* synth);
    ~Voice();
    void setNoteOn();
    void setNoteOff();
    void setFrequency(double frequency);
    void setBaseFrequency(double frequency){ _base_frequency = frequency; }
    void processWave();
    float tick();
    bool noteOn() { return _noteOn; }
    int getIndex() { return _index; }
    void loadWave(float* wave, int length);
    void update();
    void resetLoop();
    void setRate(unsigned int rate);
    int waveSize() { return _wave.size(); }
    bool waveEmpty() { return _wave.empty(); }
protected:
    Synthesizer* _synth;
    int _index;
    unsigned int _wave_offset;
    unsigned int _wave_rate;
    unsigned int _wave_size;
    bool _noteOn;
    double _frequency;
    double _base_frequency;
    stk::LentPitShift _pitchShift;
    WaveLoop _wave;
    float _lastvalue;
};
}

#endif
