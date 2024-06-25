#include "audio/AudioEngine.h"
#include <functional>
#include "audio/Buffer.h"

AudioEngine::AudioEngine(int nChannels, int bufsize, int nPeriods)
: _nChannels(nChannels)
, _audio(0)
, _buffer_size(bufsize)
, _outputId(0)
, _nPeriods(nPeriods)
, _input(bufsize*nChannels*nPeriods)
, _output(bufsize*nChannels*nPeriods)
{
    init();
}

AudioEngine::~AudioEngine()
{
    stopStream();
    if (_audio)
        delete _audio;
}

void AudioEngine::init()
{
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
        _inputParameters.deviceId = _audio->getDefaultInputDevice();
        _outputParameters.deviceId = _audio->getDefaultOutputDevice();
        auto info = _audio->getDeviceInfo(_inputParameters.deviceId);
        _samplerate = info.preferredSampleRate;
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
        _outputParameters.deviceId = _audio->getDefaultOutputDevice();
        _inputParameters.deviceId = _audio->getDefaultInputDevice();
    } catch(...) {
        _audio = 0;
    }
}

void AudioEngine::probeChoosenDevice(RtAudio::Api api)
{
    try {
        _audio = new RtAudio(api);
        if (!_audio) throw 1;
        _outputParameters.deviceId = _audio->getDefaultOutputDevice();
        _inputParameters.deviceId = _audio->getDefaultInputDevice();
        fprintf(stderr, "Load SUCCESS\n");
    } catch(...) {
        fprintf(stderr, "Load FAILED\n");
    }
}

void AudioEngine::startStream(int flags)
{
    if (!_audio)
        return;
    _inputParameters.nChannels = _nChannels;
    _outputParameters.nChannels = _nChannels;
    try {
        _audio->openStream(  (flags & STREAM_OUTPUT) ? &_outputParameters : nullptr,
                             (flags & STREAM_INPUT ) ? &_inputParameters : nullptr,
                              RTAUDIO_FLOAT32,
                              _samplerate,
                              &_buffer_size,
                              AudioEngine::audioCallback,
                              (void*) this );
    } catch(...) {
        return;
    }
    _audio->startStream();
}

void AudioEngine::readBuffer(void* data, unsigned int nFrames)
{
    _output.read((float*) data, nFrames*_nChannels);
}

void AudioEngine::fillBuffer(void* data, unsigned int nFrames)
{
    _input.write((float*) data, nFrames*_nChannels);
}

void AudioEngine::stopStream()
{
    if (_audio->isStreamRunning()) _audio->stopStream();
    if (_audio->isStreamOpen()) _audio->closeStream();
}

int AudioEngine::audioCallback(void * output,
                               void * input,
                               unsigned int nFrames,
                               double streamTime,
                               RtAudioStreamStatus status,
                               void * obj)
{
    AudioEngine *engine = reinterpret_cast<AudioEngine*>(obj);
    if (rtOutBuf)
        engine->readBuffer(output, nFrames);
    if (rtInBuf)
        engine->fillBuffer(input, nFrames);
    return 0;
}
