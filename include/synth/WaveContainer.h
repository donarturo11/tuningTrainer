#ifndef WAVE_CONTAINER_H
#define WAVE_CONTAINER_H
#include "synth/common.h"
#include <vector>

namespace Synth {
class WaveContainer
{
public:
    WaveContainer();
    ~WaveContainer();
    void push_back(float v) { _wave.push_back(v); }
    void resize(unsigned int i);
    int size() { return _wave.size(); }
    bool empty() { return _wave.empty(); }
    void operator=(std::vector<float> v) { _wave = v; }
    void loadWave(std::vector<float> v);
    float operator[](int idx) { &_wave[idx]; }
    float* arrayPtr() { return &_wave[0]; }
    void write(float value);
    float read();
    float read(float* values);
    float readAt(unsigned int idx) { return _wave[idx]; }
    float writeAt(unsigned int idx, float value) { _wave[idx]=value; }
    
    void setWriteOffset(unsigned int i) { _write_offset = i; }
    void setReadOffset(unsigned int i) { _read_offset = i; }
private:
    void updateOffset(unsigned int &offset);
protected:
    std::vector<float> _wave;
    unsigned int _size;
    unsigned int _read_offset;
    unsigned int _write_offset;
};
}

#endif // WAVE_CONTAINER_H