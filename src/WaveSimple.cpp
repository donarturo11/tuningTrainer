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
  sine_ = new SineWave();
  pitchShift_ = new LentPitShift();
  baseFrequency_ = 440.0;
  loopGain_ = 0.0;
  this->setPressed(0);
  
}  

WaveSimple :: ~WaveSimple( void )
{
  
}

void WaveSimple :: loadWave(std::string filename, bool raw)
{
    try {
          
          loop_->openFile(filename, raw);
          setGood();
        }
    catch(...) // if loading sample fails, set sine generator
        {
           setBad();

        }
}




void WaveSimple :: noteOn( StkFloat frequency, StkFloat amplitude )
{
  
  this->loopGain_=amplitude;
  this->setFrequency( frequency );
  
  if(this->good_) this->loop_->reset();
  
  
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
  if (isGood()) pitchShift_->setShift(frequency/baseFrequency_);
  else sine_->setFrequency(frequency);
}

void WaveSimple :: setPressed(bool pressed)
{
    this->pressed_ = pressed;
}

bool WaveSimple :: isPressed()
{
    return this->pressed_;
}

void WaveSimple::setGood()
{
    this->good_=1;
}

void WaveSimple::setBad()
{
    this->good_=0;
}

bool WaveSimple :: isGood()
{
    return this->good_;    
}



} // stk namespace
