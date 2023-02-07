#include "synth/WaveVector.h"
#include <iostream>
namespace Synth {
WaveVector::WaveVector() : WaveContainer{}
{
    std::cerr << "WaveVector c-tor\n";
    std::cerr << "Read offset: " << _read_offset << "\n";
    std::cerr << "Write offset: " << _write_offset << "\n";
}

WaveVector::~WaveVector()
{

}

void WaveVector::loadWave(std::vector<float> v)
{
    _wave_vec = v;
    _wave = getArray();
    _size = _wave_vec.size();
}


void WaveVector::resize(unsigned int i)
{ 
    _wave = 0;
    _wave_vec.resize(i);
    _size = _wave_vec.size();
    _wave = &_wave_vec[0];
}

} // namespace Synth
