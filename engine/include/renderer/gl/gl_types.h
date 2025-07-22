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



/** @brief Represents a framebuffer in opengl */
typedef struct gl_framebuffer
{
  u32 buffer;   // the buffer index in opengl

} gl_framebuffer;

#endif // FZY_RENDERER_OPENGL
