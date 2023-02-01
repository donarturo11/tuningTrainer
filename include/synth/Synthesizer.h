#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
#include <vector>
#include "audio/AudioSource.h"
#include "synth/Voice.h"
#include "synth/WaveContainer.h"
#include "synth/common.h"

namespace Synth {
class Synthesizer : public AudioSource
{
public:
    Synthesizer();
    Synthesizer(int voices);
    ~Synthesizer();
    void sendNoteOn(int index);
    void sendNoteOff(int index);
    void sendFrequencyChange(int index, double frequency);
    void addVoice();
    void setPolyphony(int voices);
    void printNotesOn(); /* to remove */
    void loadWave(std::vector<float> s);
    float tick();
    void setNotesOn();
    void setRate(unsigned int rate);
    void setBaseFrequency(float freq);
    unsigned int waveSize() { return _wave->size(); }
    WaveContainer* wave() { return _wave; }
protected:
    VoicesContainer _voices;
    std::vector<int> _notesOn;
    WaveContainer* _wave;
    unsigned int _samplerate;
    float _base_frequency;
};
}
#endif