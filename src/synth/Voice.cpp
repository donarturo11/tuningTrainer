#include "synth/Voice.h"
#include "stk/LentPitShift.h"
#include <iostream>
namespace Synth {
Voice::Voice()
{
    _index = Voice::index;
    _noteOn = false;
    fprintf(stderr, "Voice c-tor, index: %i\n", _index);
    resetLoop();
    Voice::index++;
}

Voice::~Voice()
{
    
}

void Voice::loadWave(Samples wave)
{
    _wave.clear();
    _wave = wave; 
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

float Voice::tick()
{
    if (_wave.empty() || !_noteOn) return 0;
    float value = _pitchShift.tick(_wave[_wave_offset]);
    if ( _wave_offset < waveSize())
        _wave_offset++;
    else resetLoop();
    return value;
}
    
} // namespace Synth