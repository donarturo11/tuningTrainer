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
    probeDevices();
}

void AudioEngine::probeJack()
{
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);
    bool success = false;
    for (auto api : apis) {
        if (api == RtAudio::Api::UNIX_JACK) {
            success = true;
        }
    }
    if(!success) return;
    try {
        _audio = new RtAudio(RtAudio::Api::UNIX_JACK);
        int deviceCount = _audio->getDeviceCount();
        if (!deviceCount) throw -1;
        std::cerr << "JACK Success\n";
    } catch(...) {
        _audio = 0;
        success = false;
        std::cerr << "JACK Failed\n";
        return;
    }
    if (_audio->getDeviceCount()) {
        _outputId = _audio->getDefaultOutputDevice();
        auto info = _audio->getDeviceInfo(_outputId);
        this->_samplerate = info.preferredSampleRate;
        _jack = true;
    }
}

void AudioEngine::probeDevices()
{
    _jack = false;
    probeJack();
    if (_audio) return;
    try {
        _audio = new RtAudio();
        _outputId = _audio->getDefaultOutputDevice();
    } catch(...) {
        _audio = 0;
    }
}

void AudioEngine::probeChoosenDevice(RtAudio::Api api)
{
    try {
        _audio = new RtAudio(api);
        if (!_audio) throw 1;
        _outputId = _audio->getDefaultOutputDevice();
        fprintf(stderr, "Load SUCCESS\n");
    } catch(...) {
        fprintf(stderr, "Load FAILED\n");
    }
}

void AudioEngine::initStreamParameters()
{
    if (!_audio) return;
    auto info = _audio->getDeviceInfo(_outputId);
    _streamParameters = new RtAudio::StreamParameters;
    _streamParameters->deviceId = _outputId;
    _streamParameters->nChannels = _nChannels;
    std::cerr << "Sample rate: " << _samplerate << std::endl;
    std::cerr << "Device ID: " << _outputId << std::endl;
}

void AudioEngine::startStream()
{
    if (!_audio || !_audioSource)
        return;
    initStreamParameters();
    try {
        _audio->openStream(_streamParameters, NULL, RTAUDIO_FLOAT32, _samplerate, &_buffer_size, &AudioEngine::audioCallback, (void*) _audioSource /* (void*) synth */);
    } catch(...) {
        return;
    }
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

