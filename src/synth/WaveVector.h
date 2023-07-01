#ifndef WAVE_VECTOR_H
#define WAVE_VECTOR_H
#include "synth/common.h"
#include "synth/WaveContainer.h"
#include <vector>

namespace Synth {
class WaveContainer;
class WaveVector : public WaveContainer
{
public:
    WaveVector();
    ~WaveVector();
    float* getArray() {return &_wave_vec[0]; }
    void resize(unsigned int i);
    bool empty() override { return _wave_vec.empty(); }
    void operator=(std::vector<float> v) { _wave_vec = v; }
    void loadWave(std::vector<float> v);
protected:
    std::vector<float> _wave_vec;
};
}

#endif // WAVE_VECTOR_H
