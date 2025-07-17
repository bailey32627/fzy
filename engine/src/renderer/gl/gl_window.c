#ifdef FZY_RENDERER_OPENGL

#include "renderer/fzy_window.h"
#include "core/fzy_logger.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_properties.h>

#include <glad/glad.h>

static b8 initialized = false;
static SDL_Window* window = NULL;
static SDL_GLContext gl_context = NULL;
static i32 window_width = 0;
static i32 window_height = 0;

b8 window_initialize( const char *title, i32 width, i32 height )
{
  if( initialized )
  {
    FZY_ERROR( "window_initialize :: window is already initialized" );
    return false;
  }

  // Set OpenGL attributes BEFORE creating the window
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  window = SDL_CreateWindow(
        title,                                // window title
        width,                                // width, in pixels
        height,                               // height, in pixels
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

  if( !window )
  {
    FZY_ERROR( "window_initialize :: Failed to create SDL window: %s", SDL_GetError() );
    return false;
  }

  gl_context = SDL_GL_CreateContext( window );
  if( !gl_context )
  {
    FZY_ERROR( "window_initialize :: Failed to create OpenGL context: %s", SDL_GetError() );
    return false;
  }

  SDL_GL_MakeCurrent( window, gl_context );

  if( !gladLoadGLLoader( (GLADloadproc)SDL_GL_GetProcAddress ) )
  {
    FZY_ERROR( "window_initialize :: failed to initialize GLAD" );
    SDL_GL_DestroyContext( gl_context );
    SDL_DestroyWindow( window );
    window = NULL;
    gl_context = NULL;
    return false;
  }

  initialized = true;
  return true;
} // -------------------------------------------------------------------------

void window_shutdown( void )
{
  if( gl_context )
  {
    SDL_GL_DestroyContext( gl_context );
  }
  if( window )
  {
    SDL_DestroyWindow( window );
  }
} // -------------------------------------------------------------------------

void window_swap_buffers( void )
{
  SDL_GL_SwapWindow( window );
} // -------------------------------------------------------------------------

i32 window_get_width( void )
{
  return window_width;
} // -------------------------------------------------------------------------

i32 window_get_height( void )
{
  return window_height;
} // -------------------------------------------------------------------------

f32 window_get_aspect_ratio( void )
{
  return ( window_height != 0 ) ? (f32)window_width / (f32)window_height : 1.0f;
} // -------------------------------------------------------------------------

void window_set_width_height( i32 width, i32 height )
{
  window_width = width;
  window_height = height;
} // -------------------------------------------------------------------------

void window_set_fullscreen( b8 fullscreen )
{
  SDL_SetWindowFullscreen( window, fullscreen );
} // --------------------------------------------------------------------------

#endif
