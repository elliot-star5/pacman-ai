#ifndef __LTimer_H_

#define __LTimer_H_

#include "global.h"

// Defination for initializing LTimer struct
#define _LTimer \
  { \
    .mStartTicks = 0,\
    .mPausedTicks = 0,\
    .mPaused = false,\
    .mStarted = false \
  }



// The application time based timer
struct LTimer
{
  // The clock time when the timer started
  Uint32 mStartTicks;
  
  // The clock time when the timer paused
  Uint32 mPausedTicks;


  // The timer status
  bool mPaused;
  bool mStarted;
};



// The various clock actions
void ltimer_start(struct LTimer *self);
void ltimer_stop(struct LTimer *self);
void ltimer_pause(struct LTimer *self);
void ltimer_unpause(struct LTimer *self);


// Gets the timer's time
Uint32 ltimer_getTicks(struct LTimer *self);

// Checks the status of the timer
bool ltimer_isStarted(struct LTimer *self);
bool ltimer_isPaused(struct LTimer *self);



#endif
