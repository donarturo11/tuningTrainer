#include "WaveSimpleMixer.h"
namespace stk {
WaveSimpleMixer::WaveSimpleMixer()
{

}

WaveSimpleMixer::~WaveSimpleMixer()
{
    std::cout << "Destroy Mixer" << std::endl;
}

StkFloat WaveSimpleMixer::tick()
{
    StkFloat outValue=0.0;
    for (WaveSimple *synth : m_instruments)
    {
        if (synth->isPressed()) {
            //std::cout << "is Pressed: " << synth << std::endl;
            outValue+=synth->tick();
            //outValue=0.0;
        }
    }
    return outValue;
}

void WaveSimpleMixer::addInstrument(WaveSimple* synth)
{
    this->m_instruments.push_back(synth);
}




} // namespace stk
