#include "synth/Synthesizer.h"
#include <iostream>
namespace Synth {
Synthesizer::Synthesizer() : _wave_vec{ new WaveVector() }
{
    fprintf(stderr, "Synthesizer c-tor\n");
}

Synthesizer::Synthesizer(int voices) : _wave_vec{ new WaveVector() }
{
    fprintf(stderr, "Synthesizer c-tor\n");
    setPolyphony(voices);
}

Synthesizer::~Synthesizer()
{
    
}

void Synthesizer::loadWave(std::vector<float> s) {
    if (s.empty()) return;
    _wave_vec->loadWave(s);
    for (auto v : _voices)
        v->update();
}

float Synthesizer::tick()
{
    float value = 0;
    for (Voice* v : _voices )
        if (v->noteOn())
            value += v->tick();
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
    _voices.push_back(new Voice(this));
}

void Synthesizer::setRate(unsigned int rate)
{
    for (auto v : _voices)
        v->setRate(rate);
}

void Synthesizer::setBufferSize(unsigned int buffersize)
{

}

void Synthesizer::setBaseFrequency(float freq)
{
    _base_frequency = freq;
    for (auto v : _voices)
        v->setBaseFrequency(freq);
}
    
    
} // namespace Synth

