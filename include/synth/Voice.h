#ifndef VOICE_H
#define VOICE_H

namespace Synth {
class Voice
{
public:
    inline static int index=0;
    Voice();
    ~Voice();
    void setNoteOn();
    void setNoteOff();
    void setFrequency(double frequency);
    bool noteOn() { return _noteOn; }
    int getIndex() { return _index; }
protected:
    int _index;
    bool _noteOn;
    double _frequency;
};
}

#endif