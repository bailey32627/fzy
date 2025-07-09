#pragma once

#include "defines.h"

/*
  Interface for the engines core features.  This is used to udpate the event subsystem
  and input driven events
*/

/*
  @brief Intializes the core subsystem of the engine ( memory, inputs, events, logger, main timer, todo: pools ) and
    creates a main window
  @param title - title of the window
  @returns b8 - true if all subsystems initialize successfully
*/
FZY_API b8 fzy_initialize( const char* title );

/*
  @brief Shutdown the engine and frees all resources held by the memory manager
*/
FZY_API void fzy_shutdown( void );

/*
  @brief Begins the frame timer for this iteration of the subsystems
*/
FZY_API void fzy_tick_begin( void );

/*
  @brief Ends the frame timer for this iteration of the subsystems
*/
FZY_API void fzy_tick_end( void );

/*
  @brief Gets the last frame time
  @return f32 - the delta time of the last frame
*/
FZY_API f32 fzy_delta_time( void );

FZY_API void fzy_set_suspend( b8 suspend );

FZY_API b8 fzy_is_running( void );
