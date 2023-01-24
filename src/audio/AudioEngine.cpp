#include "audio/AudioEngine.h"

AudioEngine::AudioEngine()
{
    init();
}

AudioEngine::~AudioEngine()
{
    stopStream();
    _audioSource = 0;
    if (_audio)
        delete _audio;
}

void AudioEngine::init()
{
    _audio = 0;
    _buffer_size = 512;
    _running = false;
    probeDevices();
    initStreamParameters();
}

void AudioEngine::probeJack()
{
    if (_audio) return;
       
    
    if (!_audio->getDeviceCount()) {
        _audio = 0;
        return;
    }
    
    if (_audio->getDeviceCount()) {
        _outputId = _audio->getDefaultOutputDevice();
        initStreamParameters();
    }
}

void AudioEngine::probeDevices()
{
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);
    for (auto api : apis) { 
        if (api == RtAudio::Api::UNIX_JACK) {
            probeChoosenDevice(api);
        }
    }
    
    for (auto api : apis) { 
        probeChoosenDevice(api);
        if (_audio) {
            break;
        }
    }
}

void AudioEngine::probeChoosenDevice(RtAudio::Api api)
{
    try {
        _audio = new RtAudio(api);
    } catch(...) {
        _audio = 0;
    }
}

void AudioEngine::initStreamParameters()
{
    if (!_audio) return;
    _outputId = _audio->getDefaultOutputDevice();
    auto info = _audio->getDeviceInfo(_outputId);
    _streamParameters = new RtAudio::StreamParameters;
    _streamParameters->deviceId = _audio->getDefaultOutputDevice();
    _streamParameters->nChannels = _nChannels;
    std::cerr << "Sample rate: " << _samplerate << std::endl;
    std::cerr << "Device ID: " << _outputId << std::endl;
}

void AudioEngine::startStream()
{
    if (!_audio || !_audioSource)
        return;
    auto err = _audio->openStream(_streamParameters, NULL, RTAUDIO_FLOAT32, _samplerate, &_buffer_size, &AudioEngine::audioCallback, (void*) _audioSource /* (void*) synth */);
    if (err) return;
    _audio->startStream();
}

void AudioEngine::stopStream()
{
    if (_audio->isStreamRunning()) _audio->stopStream();
    if (_audio->isStreamOpen()) _audio->closeStream();
}

int AudioEngine::audioCallback(void * outputBuffer,
                               void * inputBuffer, 
                               unsigned int nFrames, 
                               double streamTime, 
                               RtAudioStreamStatus status, 
                               void * source)
{
    unsigned int i, j;
    AudioSource *audioSource = (AudioSource *) source;
    float *buffer = (float *) outputBuffer;
    float lastValue = 0;
    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;
    // Write interleaved audio data.
    for ( i=0; i<nFrames; i++ ) {
        lastValue = audioSource ? audioSource->tick() : 0;
        for ( j=0; j<2; j++ ) {
            *buffer++ = lastValue;
        }
    }
    return 0;
    
}

