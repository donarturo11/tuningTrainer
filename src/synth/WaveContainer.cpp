#include "synth/WaveContainer.h"
#include <iostream>
namespace Synth {
WaveContainer::WaveContainer() : _read_offset{ 0 }, _write_offset{ 0 }
{
    std::cerr << "WaveContainer c-tor\n";
    std::cerr << "Read offset: " << _read_offset << "\n";
    std::cerr << "Write offset: " << _write_offset << "\n";
}

WaveContainer::~WaveContainer()
{

}

void WaveContainer::loadWave(std::vector<float> v)
{
    _wave = v;
    std::cerr << "WaveContainer::loadWave\n";
    std::cerr << "size:" << _wave.size() << "\n";
}

void WaveContainer::write(float value)
{
    if (_wave.empty()) return;
    _wave[_write_offset] = value;
    updateOffset(_write_offset);
}

float WaveContainer::read()
{
    if (_wave.empty()) return 0;
    float value = _wave[_read_offset];
    updateOffset(_read_offset);
    return value;
}

void WaveContainer::updateOffset(unsigned int &offset)
{
    if (offset < size()) offset++;
    else offset = 0;
}

void WaveContainer::resize(unsigned int i)
{ 
    _wave.resize(i);
    _size = i;
}

} // namespace Synth