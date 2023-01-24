#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
#include <vector>
#include "synth/Voice.h"
#include "synth/common.h"

namespace Synth {
class Synthesizer
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
    void printNotesOn();
    void loadWave(Samples s);
    float tick();
    void setNotesOn();
protected:
    VoicesContainer _voices;
    std::vector<int> _notesOn;
    Samples _wave;
    unsigned int _samplerate;
};
}
#endif