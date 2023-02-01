#include "synth/Voice.h"
#include "stk/LentPitShift.h"
#include <iostream>

namespace Synth {
Voice::Voice(Synthesizer* synth)
{
    _synth = synth;
    _wave_orig = synth->wave();
    _wave_size = synth->wave()->size();
    _index = Voice::index;
    _noteOn = false;
    fprintf(stderr, "Voice c-tor, index: %i\n", _index);
    fprintf(stderr, "Voice wave index: %i\n", _wave_size);
    resetLoop();
    Voice::index++;
}

Voice::~Voice()
{
    
}
/*
void Voice::loadWave(float* wave)
{
    //_wave_orig = &wave[0];
    //_wave_size = _synth->waveSize();
    //_wave.resize(_wave_size);
}
*/

void Voice::update()
{
    _wave.resize(_synth->wave()->size());
    resetLoop();
}

void Voice::setNoteOn()
{
    _noteOn = true;
    resetLoop();
    fprintf(stderr, "Voice %i noteon\n", _index);
}

void Voice::setNoteOff()
{
    _noteOn = false;
    resetLoop();
    fprintf(stderr, "Voice %i noteoff\n", _index);
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
    _wave.setWriteOffset(0);
    _wave.setReadOffset(0);
    _wave_orig->setReadOffset(0);
}

float Voice::tick()
{
    if (_wave_orig->empty()) return 0;
    float value = _noteOn ? _wave_orig->read() : 0;
    _wave.write(value);
    return _wave.read();
}
    
} // namespace Synth