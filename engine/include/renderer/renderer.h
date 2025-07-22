#pragma once

#include "defines.h"

typedef enum render_flags
{
  COLOR = 0,
  DEPTH,
  STENCIL,

} render_flags;

/**
  @brief Initializes the renderer

  @return b8 - true if successful
*/
void renderer_initialize( void );

/**
  @brief Shuts down the renderer and releases resources held by it
*/
void renderer_shutdown( void );

/**
  @brief Allows tests to be enabled or disabled for the backend

  @param flag - The test flag to enable/disable
  @param enable - true to enable the test, false to disable
*/
void renderer_enable( u8 flag, b8 enable );

/**
  @brief Allows renderer to handle resize events

  @param width - the width of the window after resize
  @param height - the height of the window after resize
*/
void renderer_on_resized( u16 width, u16 height );

/**
  @brief Begin drawing a frame

  @param delta - the delta of the last frame
*/
void renderer_begin_frame( f32 delta );

/**
  @brief End the frame and swap the buffers
*/
void renderer_end_frame( void );

// --------------------------------------------------------------------------------
// Fonts
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Textures
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Materials
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Meshes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// indexing meshes
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// skeletal meshes
// --------------------------------------------------------------------------------
