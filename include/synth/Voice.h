#ifndef VOICE_H
#define VOICE_H
#include "synth/common.h"
#include "stk/LentPitShift.h"
namespace Synth {
class Voice
{
public:
    inline static int index=0;
    Voice();
    ~Voice();
    void setNoteOn();
    void setNoteOff();
    void setFrequency(double frequency);
    void setBaseFrequency(double frequency){ _base_frequency = frequency; }
    float tick();
    bool noteOn() { return _noteOn; }
    int getIndex() { return _index; }
    /* Wave */
    void loadWave(Samples wave);
    void resetLoop(){ _wave_offset = 0; }
    void setRate(unsigned int rate){ _wave_rate = rate; }
    int waveSize() { return _wave.size(); }
protected:
    int _index;
    unsigned int _wave_offset;
    unsigned int _wave_rate;
    bool _noteOn;
    double _frequency;
    double _base_frequency;
    stk::LentPitShift _pitchShift;
    Samples _wave;
};
}

#endif