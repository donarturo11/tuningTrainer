#ifndef SYNTH_COMMON_H
#define SYNTH_COMMON_H
#include <vector>
#include "stk/Stk.h"
namespace Synth {
class Voice;
typedef std::vector<Voice*> VoicesContainer;
typedef std::vector<float> Samples;
}
#endif