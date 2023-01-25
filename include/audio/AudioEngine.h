#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "rtaudio/RtAudio.h"
#include <vector>
#include "audio/AudioSource.h"

class NoJackError{};
class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();
    static int audioCallback(void *outputBuffer, 
                             void *inputBuffer,
                             unsigned int nFrames,
                             double streamTime,
                             RtAudioStreamStatus status,
                             void *source );                            
    void init();
    
    void probeDevices();
    void probeJack();
    void probeChoosenDevice(RtAudio::Api api);
    void connectSource(AudioSource* source){ _audioSource = source; }
    void initStreamParameters();
    void startStream();
    void stopStream();
    void setSamplerate(unsigned int r) { if (!_jack) _samplerate = r; }
    void setChannelsNumber(unsigned int n) { _nChannels = n; }

protected:
    bool _running;
    bool _jack;
    RtAudio* _audio = 0;
    RtAudio::StreamParameters* _streamParameters;
    AudioSource* _audioSource = 0;
    unsigned int _outputId;
    unsigned int _nChannels;
    unsigned int _samplerate;
    unsigned int _buffer_size;
    

};

#endif // AUDIOENGINE_H
