#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "rtaudio/RtAudio.h"
#include <vector>
#include "audio/AudioSource.h"
#include "audio/Buffer.h"

#define STREAM_OUTPUT 1
#define STREAM_INPUT 2

class NoJackError{};
class AudioEngine
{
public:
    AudioEngine(int nChannels = 1, int buffersize = 512, int nPeriods = 1);
    ~AudioEngine();
    static int audioCallback(void * rtOutBuf,
                             void * rtInBuf,
                             unsigned int nFrames,
                             double streamTime,
                             RtAudioStreamStatus status,
                             void *obj );
    void init();
    void probeDevices();
    void probeJack();
    void probeChoosenDevice(RtAudio::Api api);
    Buffer<float> * outputBuffer() { return &_output; }
    Buffer<float> * inputBuffer() { return &_input; }
    void readBuffer(void*,unsigned int);
    void fillBuffer(void*,unsigned int);
    void startStream(int flags = (STREAM_OUTPUT | STREAM_INPUT));
    void stopStream();
    void setSamplerate(unsigned int r) { if (!_jack) _samplerate = r; }
    int samplerate() const { return _samplerate; }
    int periods() const { return _nPeriods; }
    int channels() const { return _nChannels; }
    int bufferSize() const { return _buffer_size; }
    void setChannelsNumber(unsigned int n) {
        _nChannels = n;
        resizeBuffer();
        _inputParameters.nChannels = _nChannels;
        _outputParameters.nChannels = _nChannels;
    }
    void setPeriodsNumber(unsigned int n) {
        _nPeriods = n;
        resizeBuffer();
    }
    bool running() const {
        if (!_audio) return false;
        return _audio->isStreamRunning();
    }
private:
    void resizeBuffer() {
        _input.resize(_buffer_size * _nChannels * _nPeriods);
        _output.resize(_buffer_size * _nChannels * _nPeriods);
    }
protected:
    bool _jack;
    RtAudio* _audio;
    RtAudio::StreamParameters _inputParameters;
    RtAudio::StreamParameters _outputParameters;
    Buffer<float> _input;
    Buffer<float> _output;
    unsigned int _outputId;
    unsigned int _nChannels;
    unsigned int _samplerate;
    unsigned int _buffer_size;
    unsigned int _nPeriods;
    

};

#endif // AUDIOENGINE_H
