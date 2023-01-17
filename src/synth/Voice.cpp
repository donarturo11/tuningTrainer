#include "synth/Voice.h"
#include <iostream>
namespace Synth {
Voice::Voice()
{
    _index = Voice::index;
    _noteOn = false;
    fprintf(stderr, "Voice c-tor, index: %i\n", _index);
    Voice::index++;
}

Voice::~Voice()
{
    
}

void Voice::setNoteOn()
{
    _noteOn = true;
    fprintf(stderr, "Voice %i noteon\n", _index);
}

void Voice::setNoteOff()
{
    _noteOn = false;
    fprintf(stderr, "Voice %i noteoff\n", _index);
}

void Voice::setFrequency(double frequency)
{
    _frequency = frequency;
}
    
} // namespace Synth