#ifdef FZY_RENDERER_OPENGL

#include "renderer/renderer.h"
#include "renderer/fzy_window.h"

#include "core/fzy_logger.h"
#include "core/fzy_mem.h"

#include "renderer/gl/gl_types.h"

// resources
#include "renderer/resources/shader.h"


#include <glad/glad.h>

// --------------------------------------------------------------------------------
// Static functions
// --------------------------------------------------------------------------------



//---------------------------------------------------------------------------------
// implementation
// --------------------------------------------------------------------------------
void renderer_initialize( void )
{
  glEnable( GL_DEPTH_TEST ); FZY_CHECK_GL_ERROR;
  glEnable( GL_CULL_FACE );  FZY_CHECK_GL_ERROR;
  glEnable( GL_BLEND ); FZY_CHECK_GL_ERROR;
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); FZY_CHECK_GL_ERROR;

  shader_manager_initialize();

  FZY_INFO( "OpenGL renderer initialized successfully" );
} // --------------------------------------------------------------------------

void renderer_shutdown( void )
{
  shader_manager_shutdown();
} // --------------------------------------------------------------------------

void renderer_enable( u8 flag, b8 enable )
{
  switch( flag )
  {
    case DEPTH:
      if( enable ) glEnable( GL_DEPTH_TEST );
      else glDisable( GL_DEPTH_TEST );
      break;

    default: break;
  }
} // --------------------------------------------------------------------------

void renderer_on_resized( u16 width, u16 height )
{
  glViewport( 0, 0, width, height ); FZY_CHECK_GL_ERROR;
} // --------------------------------------------------------------------------

void renderer_begin_frame( f32 delta )
{
  glClearColor( 0.0, 0.0, 0.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
} // --------------------------------------------------------------------------

void renderer_end_frame( void )
{
  window_swap_buffers( );
} // --------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Fonts
// --------------------------------------------------------------------------------



#endif // FZY_RENDERER_OPENGL
