#include "AudioEngine.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>

AudioEngine::AudioEngine()
{
    std::cout << "Audio engine c-tor\n";
    init();
    startStream();
    sleep(1);
}

AudioEngine::~AudioEngine()
{
    stopStream();
    if (_audio)
        delete _audio;
}

void AudioEngine::init()
{
    _buffer_size = 512;
    probeDevices();
}

void AudioEngine::probeJack()
{
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);
    
    _audio = 0;
    for (auto api : apis) { 
        if (api == RtAudio::Api::UNIX_JACK) {
            _audio = new RtAudio(RtAudio::Api::UNIX_JACK);
        }
    }
    
    if (!_audio) return;
    
    if (!_audio->getDeviceCount()) {
        _audio = 0;
        return;
    }
    
    if (_audio->getDeviceCount()) {
        unsigned int id = _audio->getDefaultOutputDevice();
        auto info = _audio->getDeviceInfo(id);
        _samplerate = info.preferredSampleRate;
    }
}

void AudioEngine::probeDevices()
{
    probeJack();
    if (_audio)
        return;
    _audio = new RtAudio();
    _outputId = _audio->getDefaultOutputDevice();
     
}

void AudioEngine::initStreamParameters()
{
    if (!_audio) return;
    auto info = _audio->getDeviceInfo(_outputId);
    _streamParameters = new RtAudio::StreamParameters;
    _streamParameters->deviceId = _audio->getDefaultOutputDevice();
    _streamParameters->nChannels = 2;
    _samplerate = info.preferredSampleRate;
}

void AudioEngine::startStream()
{
    if (!_streamParameters)
        return;
    /* 
    _synth from another methos
    */    
    float data[] = { 0 , 0 }; /* data = address of synth */
    auto err = _audio->openStream(_streamParameters, NULL, RTAUDIO_FLOAT32, _samplerate, &_buffer_size, &AudioEngine::sawCallback, (void*)&data /* (void*) synth */);
    if (err) return;
    _audio->startStream();
}

void AudioEngine::stopStream()
{
    if (_audio->isStreamRunning()) _audio->stopStream();
    if (_audio->isStreamOpen()) _audio->closeStream();
}

float AudioEngine::tick()
{
    return 0;
}



int AudioEngine::audioCallback(void * outputBuffer,
                               void * inputBuffer, 
                               unsigned int nFrames, 
                               double streamTime, 
                               RtAudioStreamStatus status, 
                               void * userData)
{
    return 0;
}

int AudioEngine::nullCallback(void * outputBuffer,
                               void * inputBuffer, 
                               unsigned int nFrames, 
                               double streamTime, 
                               RtAudioStreamStatus status, 
                               void * userData)
{
  unsigned int i, j;
  float *buffer = (float *) outputBuffer;
  float *lastValues = (float *) userData;
  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;
  // Write interleaved audio data.
  for ( i=0; i<nFrames; i++ ) {
    for ( j=0; j<2; j++ ) {
      *buffer++ = lastValues[j];
      lastValues[j] = 0;
    }
  }
  return 0;   
}

int AudioEngine::sawCallback(void * outputBuffer, void * inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status, void * userData)
{
  unsigned int i, j;
  float *buffer = (float *) outputBuffer;
  float *lastValues = (float *) userData;
  if ( status )
    std::cout << "Stream underflow detected!" << std::endl;
  // Write interleaved audio data.
  for ( i=0; i<nFrames; i++ ) {
    for ( j=0; j<2; j++ ) {
      *buffer++ = lastValues[j];
      lastValues[j] += 0.005 * (j+1+(j*0.1));
      if ( lastValues[j] >= 1.0 ) lastValues[j] -= 2.0;
    }
  }
  return 0;     
    
}