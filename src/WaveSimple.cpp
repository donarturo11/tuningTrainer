/***************************************************/
/*! \class WaveSimple
    \brief Primitive wavesampler

    This class uses loaded wave file.
    It is based on Simple from stk.
    by Artur Wrona 2021.
*/
/***************************************************/

#include "WaveSimple.h"
#include "SKINImsg.h"

namespace stk {

WaveSimple :: WaveSimple( void )
{
  
  loop_ = new FileLoop();
  pitchShift_ = new LentPitShift();
  baseFrequency_ = 440.0;
  setFrequency( baseFrequency_ );
  loopGain_ = 0.0;
  this->setPressed(0);
  //playing_=false;
  
}  

WaveSimple :: ~WaveSimple( void )
{
  
}

void WaveSimple :: loadWave(std::string filename, bool raw)
{
    this->loop_->openFile(filename, raw);
}



void WaveSimple :: noteOn( StkFloat frequency, StkFloat amplitude )
{
  
  this->loopGain_=amplitude;
  this->setFrequency( frequency );
  this->loop_->reset();
  this->setPressed(1);
  
}

void WaveSimple :: noteOff(StkFloat amplitude)
{
  this->loopGain_=amplitude;
  this->setPressed(0);

}

int WaveSimple :: getSize()
{
    return this->loop_->getSize();
}

void WaveSimple :: setBaseFrequency(StkFloat frequency)
{
    this->baseFrequency_=frequency;
}

void WaveSimple :: setFrequency( StkFloat frequency )
{
  pitchShift_->setShift(frequency/baseFrequency_);
}

void WaveSimple :: setPressed(bool pressed)
{
    this->pressed_ = pressed;
}

bool WaveSimple :: isPressed()
{
    return this->pressed_;
}



} // stk namespace
