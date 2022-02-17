
#include "global.h"
#ifndef __LTimer_H_

#define __LTimer_H_

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




// Start timer
void ltimer_start(struct LTimer *self)
{
  // Start the timer
  self->mStarted = true;

  // Unpause the timer
  self->mPaused = false;

  // get the current clock time
  self->mStartTicks = SDL_GetTicks();
  self->mPausedTicks = 0;
}



/* Stop timer by setting variable to 
  stop state */
void ltimer_stop(struct LTimer *self)
{
  // Stop the timer
  self->mStarted = false;

  // Unpause the timer
  self->mPaused = false;

  // Clear ticks variables
  self->mStartTicks = 0;
  self->mPausedTicks = 0;
}


/*
   pause the timer by setting
   mStart ticks to 0 and mPauseTicks
   to Current ticks - mStartTicks
   */
void ltimer_pause(struct LTimer *self)
{
  // if the timer is running and isn't already paused
  if (self->mStarted && !self->mPaused)
  {
    // Pause the timer
    self->mPaused = true;

    // Calculate the paused ticks
    self->mPausedTicks = SDL_GetTicks() - self->mStartTicks;
    self->mStartTicks = 0;
  }
}


/* unpause the timerr
   by setting mPaused to false
   and mStartTicks equal to current ticks - 
   mPausedTicks ```means just restoring the 
   mStartTicks.```
   */


void ltimer_unpause(struct LTimer *self)
{
  // If the timer is running and paused
  if (self->mStarted && self->mPaused)
  {
    // Unpause the timer
    self->mPaused = false;

    // Restart the starting ticks
    self->mStartTicks = SDL_GetTicks() - self->mPausedTicks;

    // Restart the paused ticks
    self->mPausedTicks = 0;
  }
}

/*
   get ticks from point
   where it is been started
   and if it is paused 
   then returns mPausedTicks;
   */
Uint32 ltimer_getTicks(struct LTimer *self)
{
  // The actual timer time
  Uint32 time = 0;

  // If the timer is running
  if (self->mStarted)
  {
    // if the timer is paused
    if (self->mPaused)
    {
      // Return the number of ticks when the timer was paused
      time = self->mPausedTicks;
    }
    else
    {
      // Return the current time minus the start time
      time = SDL_GetTicks() - self->mStartTicks;
    }
  }

  return time;
}


// test timer start status
bool ltimer_isStarted(struct LTimer *self)
{
  // Timer is running and paused or unpaused
  return self->mStarted;
}


// Test timer stop status
bool ltimer_isPaused(struct LTimer *self)
{
  // Timer is running and paused
  return self->mPaused && self->mStarted;
}

#endif
