#ifndef WAVE_CONTAINER
#define WAVE_CONTAINER
namespace Synth {
class WaveContainer
{
public:
    WaveContainer(); 
    ~WaveContainer();
    void setReadOnly(){ _writable = false; }
    void setWritable(){ _writable = true; }
    void loadWave(float* wave);
    float read();
    float readAt(unsigned int idx);
    void write(float value);
    void writeAt(unsigned int idx, float value);
    void setWriteOffset(unsigned int i) { _write_offset = i; }
    void setReadOffset(unsigned int i) { _read_offset = i; }
    virtual bool empty() { return _size == 0; }
    unsigned int size() { return _size; }
private:
    void updateOffset(unsigned int &offset);    
protected:
    float* _wave;
    unsigned int _size;
    unsigned int _read_offset;
    unsigned int _write_offset;
    bool _writable;
    const float _termArray = -1000000;
};

}
#endif
