#ifdef FZY_RENDERER_OPENGL

#include "defines.h"
#include "core/fzy_hashtable.h"

#include <glad/glad.h>

void check_gl_error( void );

#ifndef FZY_CONFIG_RELEASE
#define FZY_CHECK_GL_ERROR check_gl_error()
#else
#define FZY_CHECK_GL_ERROR (void)0
#endif






/** Represents a texture in opengl */
typedef struct gl_texture
{
  u32 id;             // opengl texture id
  u32 format;         // opengl pixel format
  i32 width;          // width of the texture
  i32 height;         // height of the texture
  u32 channels;       // the number of color channels used in the texture
  u32 atlas_square;   // number of textures held by the atlas, must be a square

} gl_texture;
// ---------------------------------------------------------------------------

/** @brief Represents a framebuffer in opengl */
typedef struct gl_framebuffer
{
  u32 buffer;   // the buffer index in opengl

} gl_framebuffer;

#endif // FZY_RENDERER_OPENGL
