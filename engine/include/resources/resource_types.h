#pragma once

#include "defines.h"
#include "core/fzy_vector.h"

extern const u32 FZY_BYTE;
extern const u32 FZY_UBYTE;
extern const u32 FZY_INT;
extern const u32 FZY_UINT;
extern const u32 FZY_SHORT;
extern const u32 FZY_USHORT;
extern const u32 FZY_FLOAT;
extern const u32 FZY_DOUBLE;


b8 gl_renderer_initialize( struct renderer_backend *backend )
{
  if( !backend ) return false;

  if( !gladLoadGLLoader( SDL_GL_GetProcAddress ) )
  {
    FZY_ERROR( "opengl_renderer_initialize :: failed to initialize glad" );
    return false;
  }

  glEnable( GL_DEPTH_TEST ); FZY_CHECK_GL_ERROR;
  glEnable( GL_CULL_FACE ); FZY_CHECK_GL_ERROR;
  glEnable( GL_BLEND ); FZY_CHECK_GL_ERROR;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); FZY_CHECK_GL_ERROR;

  FZY_INFO( "OpenGL renderer initialized successfully" );
  return true;
} // --------------------------------------------------------------------------

b8 gl_renderer_shutdown( struct renderer_backend *backend )
{
  if( !backend ) return false;

  // shutdown other stuff here

  return true;
} //
void gl_renderer_enable( u8 flag, b8 enable )
{
  switch( flag )
  {
    case DEPTH:
    {
      if( enable )
        glEnable( GL_DEPTH_TEST );
      else
        glDisable( GL_DEPTH_TEST );
      break;
    }
    default: break;
  }
} // --------------------------------------------------------------------------

void gl_renderer_resized( struct renderer_backend *backend, u16 width, u16 height )
{
  // TODO: implement
} // --------------------------------------------------------------------------

b8 gl_renderer_begin_frame( struct renderer_backend* backend )
{
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  return true;
} // --------------------------------------------------------------------------

b8 gl_renderer_end_frame( struct renderer_backend* backend )
{
  window_swap();
  return true;
} // --------------------------------------------------------------------------
