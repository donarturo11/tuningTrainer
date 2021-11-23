#include "AudioEngine.h"
#include <iostream>
//#include "FileLoop.h"
//#include "rtaudio/RtAudio.h"
//#include "RtWvOut.h"



AudioEngine::AudioEngine() 
{
    std::cout << "Running audio engine" << "\nType: " << typeid(this).name() << std::endl;
    std::cout << "Audio engine address:" << this << std::endl;
    
    //m_synth = nullptr;
    //std::thread t(&AudioEngine::init, this);
    //t.detach();
    
    
}

AudioEngine::~AudioEngine()
{
    
    //t.join();
    this->setRunning(0);
    std::cout << "Stopping audio engine" << std::endl;
    //delete output;
}


void AudioEngine::init()
{
    
    probeSampleRate();
    setAudioValue(0.0);
    setRunning(true);
    
    std::thread t(&AudioEngine::start, this);
    t.detach();
    
    //start();
    
}

void AudioEngine::connectMixer(stk::WaveSimpleMixer *mixer)
{
    this->m_mixer = mixer;
    
}



void AudioEngine::start()
{
   std::cout << "Start Audio Engine" << std::endl;
   std::cout << "Address:" << this << std::endl;
   stk::StkFloat value;
   while (this->running)
   //while (true)
   {
       value=0.0;
       
       output->tick(m_mixer->tick());
       
   }
        
}

void AudioEngine::stop()
{
    
    std::cout << "Stop" << std::endl;
    setRunning(0);
    delete output;
    
        
}

void AudioEngine::probeSampleRate()
{
    unsigned int sRates[]={44100, 48000, 96000};
    for (int i=0; i<3; i++)
    {
        try
        {
            std::cout << "Trying: " << sRates[i] << std::endl;
            stk::Stk::setSampleRate(sRates[i]);
            output = new stk::RtWvOut( 1 );
            break;
        }
        catch(...)
        {
            continue;
        }
    }
}

void AudioEngine::setAudioValue(stk::StkFloat value)
{
    this->audioValue=value;
}

void AudioEngine::printAudioValue()
{
    std::cout << this->audioValue << std::endl;
}

void AudioEngine::setRunning(bool running)
{
    this->running = running;
}





