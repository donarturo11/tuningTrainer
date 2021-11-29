#ifndef STK_WAVESIMPLE_H
#define STK_WAVESIMPLE_H

#include <thread>

#include "Instrmnt.h"
#include "FileLoop.h"
#include "LentPitShift.h"
#include "SineWave.h"

namespace stk {

/***************************************************/
/*! \class WaveSimple
    \brief Primitive wavesampler

    This class uses loaded wave file.
    It is based on Simple from stk.
    by Artur Wrona 2021.
*/
/***************************************************/

class WaveSimple : public Instrmnt
{
 public:
  //! Class constructor.
  /*!
    An StkError will be thrown if the rawwave path is incorrectly set.
  */
  WaveSimple( void );

  //! Class destructor.
  ~WaveSimple( void );
  
  
  //! Load wavefile
  void loadWave(std::string filename, bool raw=false);
  
  void setBaseFrequency(StkFloat frequency);

  //! Set instrument parameters for a particular frequency.
  void setFrequency( StkFloat frequency );

  //! Start a note with the given frequency and amplitude.
  void noteOn( StkFloat frequency, StkFloat amplitude );

  //! Stop a note with the given amplitude (speed of decay).
  void noteOff( StkFloat amplitude = 0.0 );
  
  //! Compute and return one output sample.
  StkFloat tick( unsigned int channel = 0 );

  int getSize();

  StkFrames& tick( StkFrames& frames, unsigned int channel = 0 );
  
  void setPressed(bool b=0);
  bool isPressed();
  bool isGood();
 
 private:
  void initWave();
  void initSine();
  void setGood();
  void setBad();
 
 protected:

  FileLoop *loop_;
  SineWave *sine_;
  StkFloat  baseFrequency_;
  StkFloat  loopGain_;
  LentPitShift *pitchShift_;
  bool pressed_;
  bool good_;

};

inline StkFloat WaveSimple :: tick( unsigned int )
{
  if (isGood()) lastFrame_[0] = loopGain_ * pitchShift_->tick(loop_->tick());
  else lastFrame_[0] = loopGain_ * sine_->tick();
  return lastFrame_[0];
}

inline StkFrames& WaveSimple :: tick( StkFrames& frames, unsigned int channel )
{
  unsigned int nChannels = lastFrame_.channels();
#if defined(_STK_DEBUG_)
  if ( channel > frames.channels() - nChannels ) {
    oStream_ << "WaveSimple::tick(): channel and StkFrames arguments are incompatible!";
    handleError( StkError::FUNCTION_ARGUMENT );
  }
#endif

  StkFloat *samples = &frames[channel];
  unsigned int j, hop = frames.channels() - nChannels;
  if ( nChannels == 1 ) {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop )
      *samples++ = tick();
  }
  else {
    for ( unsigned int i=0; i<frames.frames(); i++, samples += hop ) {
      *samples++ = tick();
      for ( j=1; j<nChannels; j++ )
        *samples++ = lastFrame_[j];
    }
  }

  return frames;
}

} // stk namespace

#endif
