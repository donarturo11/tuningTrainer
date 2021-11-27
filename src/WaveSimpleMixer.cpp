#include "WaveSimpleMixer.h"
namespace stk {
WaveSimpleMixer::WaveSimpleMixer()
{

}

WaveSimpleMixer::~WaveSimpleMixer()
{
    
}

StkFloat WaveSimpleMixer::tick()
{
    StkFloat outValue=0.0;
    for (WaveSimple *synth : m_instruments)
    {
        if (synth->isPressed()) {
            outValue+=synth->tick();
        }
    }
    return outValue;
}

void WaveSimpleMixer::addInstrument(WaveSimple* synth)
{
    this->m_instruments.push_back(synth);
}




} // namespace stk
