#include "AudioEngine.h"

AudioEngine::AudioEngine() 
{

}

AudioEngine::~AudioEngine()
{
    this->setRunning(0);   
}


void AudioEngine::init()
{
    
    probeSampleRate();
    setAudioValue(0.0);
    setRunning(true);
    
    std::thread t(&AudioEngine::start, this);
    t.detach();
    
}

void AudioEngine::connectMixer(stk::WaveSimpleMixer *mixer)
{
    this->m_mixer = mixer;
    
}



void AudioEngine::start()
{
   stk::StkFloat value;
   while (this->running)
   {
       value=0.0;
       output->tick(m_mixer->tick());
   }
        
}

void AudioEngine::stop()
{
    //std::cout << "Stop" << std::endl;
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



void AudioEngine::setRunning(bool running)
{
    this->running = running;
}





