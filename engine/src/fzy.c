#include "fzy.h"
#include "core/fzy_logger.h"
#include "core/fzy_clock.h"
#include "core/fzy_mem.h"
#include "core/fzy_event.h"
#include "core/fzy_input.h"
#include "renderer/fzy_window.h"

#include <SDL3/SDL.h>


// Static data
b8 initialized = false;

b8 is_running = false;
b8 is_suspended = false;

clock _clock; // the main timer in the app
f32 delta;   // the delta time
u64 running_time; // total run time

u64 current_time;
u64 last_time;  // time stamp for last frame
u64 frame_start_time; // start time for the frame

const f32 target_frame_time = 1.0f / 60.0f;  // ideal frame timer

u32 frame_count; // the frame counter

//-----------------------------------------------------------------------------

// helper function to process events
static void process_events( void )
{
  SDL_Event event;

  while( SDL_PollEvent(&event) )
  {
    switch( event.type )
    {
      case SDL_EVENT_MOUSE_WHEEL:
        input_process_mouse_wheel( (i8)event.wheel.y );
        break;

      case SDL_EVENT_WINDOW_RESIZED:
        //renderer_on_resized( event.window.data1, event.window.data2 );
        break;

      case SDL_EVENT_QUIT:
        is_running = false;
        break;

      default:
        break;
    }
  }
} // --------------------------------------------------------------------------


b8 fzy_initialize( const char* title )
{
  if( initialized )
  {
    FZY_ERROR( "fzy_initialize :: initialization called more than once." );
    return false;
  }

  // initialize SDL
  if((SDL_Init( SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)==-1))
  {
    FZY_ERROR("Could not initialize SDL: %s.\n", SDL_GetError());
  }

  // initialize subsystems
  if( !memory_initialize() )
  {
    FZY_ERROR( "fzy_initialize :: Failed to initialize the memory manager" );
    return false;
  }

  if( !event_system_initialize() )
  {
    FZY_ERROR("fzy_initialize :: failed to initialize the event system" );
    return false;
  }

  if( !input_system_initialize() )
  {
    FZY_ERROR( "fzy_initialize :: failed to initialize the input system" );
    return false;
  }

  if( !window_initialize( title, 1200, 800 ) )
  {
     FZY_ERROR( "fzy_initialize :: Failed to initialize the window" );
     return false;
  }

  initialized = true;

  clock_start( &_clock );
  clock_update( &_clock );
  last_time = _clock.elasped;
  running_time = 0;
  frame_count = 0;
  delta = 0.0;

  is_running = true;
  is_suspended = false;

  return true;
} // --------------------------------------------------------------------------

void fzy_shutdown( void )
{
  if( !input_system_shutdown() ) FZY_ERROR( "fzy_shutdown :: failed to shutdown the input system" );
  if( !event_system_shutdown() ) FZY_ERROR( "fzy_shutdown :: failed to shutdown the event system" );
  if( !memory_shutdown( ) ) FZY_ERROR( "fzy_shutdown :: failed to shutdown memory system" );

  SDL_Quit();
} // --------------------------------------------------------------------------

void fzy_tick_begin( void )
{
  process_events();

  if( is_suspended ) return;

  // update clock and get delta time
  clock_update( &_clock );
  current_time = _clock.elasped;
  delta = (f32)( current_time - last_time );
  frame_start_time = SDL_GetTicks();
} // --------------------------------------------------------------------------

void fzy_tick_end( void )
{
  u64 frame_end_time = SDL_GetTicks();
  u64 frame_elasped_time = frame_end_time - frame_start_time;
  running_time += frame_elasped_time;
  f64 remaining_seconds = target_frame_time - frame_elasped_time;

  if( remaining_seconds > 0 )
  {
    u32 remaining_ms = ( (u32)remaining_seconds * 1000 );

    //if time is left give it back to the os
    b8 limit_frames = false;
    if( remaining_ms > 0 && limit_frames )
    {
      SDL_Delay( remaining_ms - 1 );
    }

    frame_count++;
  }
  /*
   Note: Input update/state copy should always be handled after any input
    should be recorded.  IE before this line.  As a safety input should be
    the last thing updated before the frame ends
  */
  input_system_update( );

  // update last time
  last_time = current_time;
} // --------------------------------------------------------------------------

f32 fzy_delta_time( void )
{
  return (f32)delta;
} // --------------------------------------------------------------------------

void fzy_set_suspend( b8 suspend )
{
  is_suspended = suspend;
} // --------------------------------------------------------------------------

b8 fzy_is_running( void )
{
  return is_running;
} // --------------------------------------------------------------------------
