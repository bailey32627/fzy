#ifdef FZY_RENDERER_OPENGL

#include "renderer/gl/gl_types.h"

#include "core/fzy_logger.h"
#include "core/fzy_string.h"

#include <glad/glad.h>

void check_gl_error( void )
{
  GLenum e = glGetError();

  while( e != GL_NO_ERROR )
  {
    char error[ 2048 ];
    switch( e )
    {
      case GL_INVALID_OPERATION:				      string_copy( error, 2048, "INVALID_OPERATION" );		break;
      case GL_INVALID_ENUM:					          string_copy( error, 2048, "GL_INVALID_ENUM");		break;
      case GL_INVALID_VALUE:					        string_copy( error, 2048, "GL_INVALID_VALUE");		break;
      case GL_OUT_OF_MEMORY:					        string_copy( error, 2048, "GL_OUT_OF_MEMORY");		break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:	string_copy( error, 2048, "GL_INVALID_FRAMEBUFFER_OPERATION");		break;
      default:								                string_copy( error, 2048, "Somethings wrong" ); break;
    }

    FZY_ERROR( "OpenGL error: { %s }", error );
  }
} // ------------------------------------------------------------------------

#endif // FZY_RENDERER_OPENGL
