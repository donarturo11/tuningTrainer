#include "synth/WaveContainer.h"
#include <iostream>
namespace Synth {

WaveContainer::WaveContainer() : _writable{true}, _read_offset{ 0 }, _write_offset{ 0 }
{

}

WaveContainer::~WaveContainer()
{

}

void WaveContainer::loadWave(float* wave)
{
    _size = 0;
    _wave = 0;
    if (!wave) return;
    _wave = wave;
    while (*wave++ != _termArray) {
        _size++;
    }
}

void WaveContainer::write(float value)
{   
    if (empty() || !_writable) return;
    _wave[_write_offset] = value;
    updateOffset(_write_offset);
}

float WaveContainer::readAt(unsigned int idx)
{   
    if (idx >= _size) return 0;
    return _wave[idx];
}

void WaveContainer::writeAt(unsigned int idx, float value)
{
    if ( (idx >= _size) || !_writable ) return;
    _wave[idx]=value;
}

float WaveContainer::read()
{   
    if (empty()) return 0;
    float value = _wave[_read_offset];
    updateOffset(_read_offset);
    return value;
}

void WaveContainer::updateOffset(unsigned int &offset)
{
    if (offset < size()) offset++;
    else offset = 0;
}


}
