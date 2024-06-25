#include "synth/Voice.h"
#include "stk/LentPitShift.h"

namespace Synth {
Voice::Voice(Synthesizer* synth)
{
    _wave_size = 0;
    _synth = synth;
    _index = Voice::index;
    _noteOn = false;
    update();
    Voice::index++;
}

Voice::~Voice()
{
    
}

void Voice::loadWave(float* wave, int length)
{
    _wave.loadWave(wave, length);
}


void Voice::update()
{
    auto wave = _synth->wave();
    _wave.loadWave( wave.data(), wave.size() );
    resetLoop();
}

void Voice::setNoteOn()
{
    _noteOn = true;
    resetLoop();
}

void Voice::setNoteOff()
{
    _noteOn = false;
    resetLoop();
}

void Voice::setFrequency(double frequency)
{
    _frequency = frequency;
    _pitchShift.setShift(_frequency/_base_frequency);
}


void Voice::setRate(unsigned int rate)
{
    _wave_rate = rate;
    stk::Stk::setSampleRate(rate);
}

void Voice::resetLoop() 
{ 
    _wave.setReadOffset(0);
}

float Voice::tick()
{
    if (_wave.empty()) return 0;
    _lastvalue = _noteOn ? _pitchShift.tick(_wave.read()) : 0;
    return _lastvalue;
}
    
} // namespace Synth
