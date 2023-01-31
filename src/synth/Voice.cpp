#include "synth/Voice.h"
#include "stk/LentPitShift.h"
#include <iostream>

namespace Synth {
Voice::Voice(Synthesizer* synth)
{
    _synth = synth;
    _index = Voice::index;
    _noteOn = false;
    fprintf(stderr, "Voice c-tor, index: %i\n", _index);
    resetLoop();
    Voice::index++;
}

Voice::~Voice()
{
    
}

void Voice::loadWave(float* wave)
{
    _wave_orig = &wave[0];
    _wave_size = _synth->waveSize();
    _wave.resize(_wave_size);
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

float Voice::tick()
{
    if (waveEmpty() || !_noteOn) return 0;
    float value = _pitchShift.tick(_wave_orig[_wave_offset]);
    if ( _wave_offset < waveSize())
        _wave_offset++;
    else resetLoop();
    return value;
}
    
} // namespace Synth