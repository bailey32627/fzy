#pragma once

#include "defines.h"

/*
  Interface for the engine
*/

/*
  @brief Initalizes all the subsystems of the engine
  @brief backend - Defines the renderer backend to use
  @return true if successful
*/
FZY_API b8 fzy_initialize( void );

/*
  @brief Updates the engine and passes the elasped time of the last frame to the subsystems
  @param deltaTime - The duration of the last frame
  @return b8 - true if successful
*/
FZY_API b8 fzy_update( f32 deltaTime );

/*
  @brief Shutdown the engine and frees all resources held by the memory manager
*/
FZY_API void fzy_shutdown( void );
