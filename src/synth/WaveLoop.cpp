#include "synth/WaveLoop.h"
namespace Synth {
WaveLoop::WaveLoop() : _writable{true}, _read_offset{ 0 }, _write_offset{ 0 }, _size{ 0 }, _wave(nullptr)
{}

WaveLoop::~WaveLoop()
{}

void WaveLoop::loadWave(float* wave, int size)
{
    _read_offset = 0;
    _write_offset = 0;
    _size = 0;
    _wave = 0;
    if (!wave) return;
    _wave = wave;
    _size = size;
}

void WaveLoop::write(float value)
{   
    if (empty() || !_writable) return;
    _wave[_write_offset] = value;
    _mutex.lock();
    _write_offset = (_write_offset + 1) % _size;
    _mutex.unlock();
}

float WaveLoop::readAt(unsigned int idx)
{   
    if (idx >= _size) return 0;
    return _wave[idx];
}

void WaveLoop::writeAt(unsigned int idx, float value)
{
    if ( (idx >= _size) || !_writable ) return;
    _wave[idx]=value;
}

float WaveLoop::read()
{   
    if (empty()) return 0.00;
    float value = _wave[_read_offset];
    _mutex.lock();
    _read_offset = (_read_offset + 1) % _size;
    _mutex.unlock();
    return value;
}

}
