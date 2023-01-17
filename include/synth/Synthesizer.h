#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H
#include <vector>
#include "synth/Voice.h"

namespace Synth {
typedef std::vector<Voice*> VoicesContainer;
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
    VoicesContainer getNotesOn();
protected:
    VoicesContainer _voices;
};
}
#endif