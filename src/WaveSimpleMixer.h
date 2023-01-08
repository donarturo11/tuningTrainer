#ifndef STK_WAVESIMPLEMIXER_H
#define STK_WAVESIMPLEMIXER_H

#include <vector>

#include "stk/Stk.h"
#include "WaveSimple.h"
#include "AudioEngine.h"

namespace stk {


class WaveSimpleMixer
{
 public:
 WaveSimpleMixer();
 ~WaveSimpleMixer();
 std::vector <WaveSimple*> m_instruments;
 
 StkFloat tick();
 void addInstrument(WaveSimple* synth);
 
 private:

 protected:
 
 


};

} // namespace stk
#endif
