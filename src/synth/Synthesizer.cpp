#include "synth/Synthesizer.h"
#include <iostream>
namespace Synth {
Synthesizer::Synthesizer()
{
    fprintf(stderr, "Synthesizer c-tor\n");
}

Synthesizer::Synthesizer(int voices)
{
    fprintf(stderr, "Synthesizer c-tor\n");
    setPolyphony(voices);
}

Synthesizer::~Synthesizer()
{
    
}

void Synthesizer::setNotesOn()
{
    std::vector<int> notesOn;
    for (auto voice : _voices) {
        if (voice->noteOn()) {
            notesOn.push_back(voice->getIndex());
        }
    }
    _notesOn.clear();
    _notesOn = notesOn;
}

void Synthesizer::loadWave(Samples s) {
    if (s.empty()) return;
    for (auto v : _voices)
        v->loadWave(s);
}

float Synthesizer::tick()
{
    float value = 0;
    if (_notesOn.empty()) return 0;
    for (int idx : _notesOn )
        value += _voices[idx]->tick();
    return value;
}

void Synthesizer::setPolyphony(int voices)
{
    if (!_voices.empty())
        return;
    _voices.clear();
    Voice::index=0;
    for (int i=0; i<voices; i++) {
        addVoice();
    }
}

void Synthesizer::sendNoteOn(int index)
{
    if (index < _voices.size())
        _voices[index]->setNoteOn();
    setNotesOn();
}

void Synthesizer::sendNoteOff(int index)
{
    if (index < _voices.size())
        _voices[index]->setNoteOff();
}

void Synthesizer::sendFrequencyChange(int index, double frequency)
{
    if (index < _voices.size())
        _voices[index]->setFrequency(frequency);
}

void Synthesizer::addVoice()
{
    _voices.push_back(new Voice);
}

void Synthesizer::setRate(unsigned int rate)
{
    for (auto v : _voices)
        v->setRate(rate);
}

void Synthesizer::setBaseFrequency(float freq)
{
    _base_frequency = freq;
    for (auto v : _voices)
        v->setBaseFrequency(freq);
}
    
    
} // namespace Synth

