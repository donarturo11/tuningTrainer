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

VoicesContainer Synthesizer::getNotesOn()
{
    VoicesContainer notesOn;
    for (auto voice : _voices) {
        if (voice->noteOn()) {
            notesOn.push_back(voice);
        }
    }
    return notesOn;
}

void Synthesizer::printNotesOn()
{
    auto notesOn = getNotesOn();
    fprintf(stderr, "Notes on: ");
    for (auto voice : notesOn)
        fprintf(stderr, "%i ", voice->getIndex());
    fprintf(stderr, "\n");
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
    printNotesOn();
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
    
    
} // namespace Synth