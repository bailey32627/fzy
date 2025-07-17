#pragma once

#include "defines.h"

/*
  @brief  This is an abstract SDL 3 window, it creates the window with the correct context
          depending on the renderer specified on build
*/

/*
  @brief creates the window
  @param title - Title to set the window to create
  @param width - width of the window to create
  @param height - height of the window to create
  @return true if successful
*/
b8 window_initialize( const char *title, i32 width, i32 height );

/*
  @brief Shuts down the window
*/
void window_shutdown( void );

/*
  @brief Swaps the back buffer for the front
*/
void window_swap_buffers( void );

/*
  @brief Gets the width of the window
  @return Width
*/
i32 window_get_width( void );

/*
  @brief Gets the height of the window
  @return Height
*/
i32 window_get_height( void );

/*
  @brief Gets the aspect ratio of the window
  @return Aspect ratio
*/
f32 window_get_aspect_ratio( void );

/*
  @brief Sets the width and height of the window
  @Should only be called by a resize event
*/
void window_set_width_height( i32 width, i32 height );

/*
  @brief Toggles the fullscreen window
  @param b8 - true to enter fullscreen
*/
void window_set_fullscreen( b8 fullscreen );
