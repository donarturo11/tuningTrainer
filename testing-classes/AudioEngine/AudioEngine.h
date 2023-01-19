#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include "rtaudio/RtAudio.h"
#include <vector>

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
                             void *userData );
    static int nullCallback(void *outputBuffer, 
                             void *inputBuffer,
                             unsigned int nFrames,
                             double streamTime,
                             RtAudioStreamStatus status,
                             void *userData );
    static int sawCallback(void *outputBuffer, 
                             void *inputBuffer,
                             unsigned int nFrames,
                             double streamTime,
                             RtAudioStreamStatus status,
                             void *userData );                             
    void init();
    
    void probeDevices();
    void probeJack();
    void initStreamParameters();
    void startStream();
    void stopStream();
private:
    float tick();
protected:
    RtAudio* _audio;
    RtAudio::StreamParameters* _streamParameters;
    unsigned int _outputId;
    unsigned int _samplerate;
    unsigned int _buffer_size;
    

};

#endif // AUDIOENGINE_H
