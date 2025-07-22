#ifdef FZY_RENDERER_OPENGL

#include "renderer/resources/shader.h"

#include "core/fzy_logger.h"
#include "core/fzy_mem.h"
#include "core/fzy_hashtable.h"
#include "core/fzy_string.h"

#include "renderer/gl/gl_types.h"

// ----------------------------------------------------------------------------------
// Structs
// ----------------------------------------------------------------------------------
/** @brief Holds the uniform data in the hashtable */
typedef struct gl_uniform
{
  i32 location;  // the location of the uniform
  u8 type;       // holds the type of uniform

} gl_uniform;
// --------------------------------------------------------------------------

/** @brief Represents a shader program in openGL */
typedef struct gl_shader
{
  u32 program;         // the shader program maintained by opengl
  hashtable *uniforms; // the uniforms used to draw this shader

} gl_shader;
// ---------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// Resource Manager
// ----------------------------------------------------------------------------------

static hashtable *shader_manager = NULL;

//-----------------------------------------------------------------------------------
// Static helper functions
// ----------------------------------------------------------------------------------

void release_uniform( void* uniform )
{
  if( !uniform ) return;
  memory_delete( uniform, sizeof( gl_uniform), MEM_TAG_SHADER );
  uniform = NULL;
} // -------------------------------------------------------------------------

void shader_destroy( shader* sdr )
{
  if( !sdr ) return;
  gl_shader *id = (gl_shader*)sdr->internal_data;
  if( id )
  {
    glDeleteProgram( id->program );
    hashtable_destroy( id->uniforms, release_uniform );
    memory_delete( id, sizeof( struct gl_shader ), MEM_TAG_SHADER );
  }
  memory_delete( sdr, sizeof( struct shader ), MEM_TAG_SHADER );
  sdr = NULL;
} // -------------------------------------------------------------------------

u32 gl_compile_shader( const char *code, u32 type )
{
  u32 id = glCreateShader( type );
  glShaderSource( id, 1, &code, 0 ); FZY_CHECK_GL_ERROR;
  glCompileShader( id ); FZY_CHECK_GL_ERROR;

  #ifdef FZY_CONFIG_DEBUG
    char t[ 128 ] = {""};
    i32 loglen;
    if( type == GL_VERTEX_SHADER ) string_copy( t, 128, "GL_VERTEX_SHADER" );
    else if( type == GL_FRAGMENT_SHADER ) string_copy( t, 128, "GL_FRAGMENT_SHADER" );

    glGetShaderiv( id, GL_INFO_LOG_LENGTH, &loglen ); FZY_CHECK_GL_ERROR;
    if( loglen )
    {
      char* log = memory_allocate( loglen, MEM_TAG_SHADER );
      glGetShaderInfoLog( id, loglen, NULL, log ); FZY_CHECK_GL_ERROR;
      FZY_ERROR( "[ %s ] %s", t, log );
      memory_delete( log, loglen, MEM_TAG_SHADER );
    }
  #endif // FZY_CONFIG_DEBUG

  i32 status;
  glGetShaderiv( id, GL_COMPILE_STATUS, &status ); FZY_CHECK_GL_ERROR;
  if( !status )
  {
    glDeleteShader( id ); FZY_CHECK_GL_ERROR;
    return 0;
  }
  return id;
} // ----------------------------------------------------------------------

u32 gl_link_shader( u32 vertex_shader, u32 fragment_shader )
{
  u32 program = glCreateProgram(); FZY_CHECK_GL_ERROR;
  glAttachShader( program, vertex_shader ); FZY_CHECK_GL_ERROR;
  glAttachShader( program, fragment_shader ); FZY_CHECK_GL_ERROR;
  glLinkProgram( program ); FZY_CHECK_GL_ERROR;

  #ifdef FZY_CONFIG_DEBUG
    i32 len;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
    if( len )
    {
      char* log = memory_allocate( len, MEM_TAG_SHADER );
      glGetProgramInfoLog( program, len, NULL, log ); FZY_CHECK_GL_ERROR;
      FZY_ERROR( "%s", log );
      memory_delete( log, len, MEM_TAG_SHADER );
    }
  #endif // FZY_CONFIG_DEBUG

  i32 status;
  glGetProgramiv( program, GL_LINK_STATUS, &status ); FZY_CHECK_GL_ERROR;
  if( status )
  {
    glDeleteProgram( program ); FZY_CHECK_GL_ERROR;
    glDeleteShader( vertex_shader ); FZY_CHECK_GL_ERROR;
    glDeleteShader( fragment_shader ); FZY_CHECK_GL_ERROR;
    program = 0;
  }
  return program;
} // -----------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// Implementation
// ----------------------------------------------------------------------------------
void shader_manager_initialize( void )
{
  shader_manager = hashtable_create( 128 );
} // -------------------------------------------------------------------------

void shader_manager_shutdown( void )
{
  hashtable_destroy( shader_manager, shader_destroy );
} // -------------------------------------------------------------------------

shader* shader_add( const char *name, const char* vertex_source, const char* fragment_source )
{
  shader* sdr = hashtable_get( shader_manager, name );
  if( sdr ) return sdr;

  u32 vertex_shader = gl_compile_shader( vertex_source, GL_VERTEX_SHADER );
  if( !vertex_shader ) return NULL;
  u32 fragment_shader = gl_compile_shader( fragment_source, GL_FRAGMENT_SHADER );
  if( !fragment_shader )
  {
    glDeleteShader( vertex_shader ); FZY_CHECK_GL_ERROR;
    return NULL;
  }

  gl_shader *id = memory_allocate( sizeof( gl_shader ), MEM_TAG_SHADER );
  id->program = gl_link_shader( vertex_shader, fragment_shader );
  if( !id->program )
  {
    FZY_ERROR( "gl_shader_create :: failed to load shaders." );
    return NULL;
  }
  id->uniforms = hashtable_create( 64 );
  sdr = memory_allocate( sizeof( struct shader ), MEM_TAG_SHADER );
  string_copy( sdr->name, MAX_NAME_LENGTH, name );
  sdr->internal_data = id;
  hashtable_set( shader_manager, name, sdr );
  return sdr;
} // -------------------------------------------------------------------------

void shader_remove( const char* name )
{
  shader *sdr = hashtable_remove( shader_manager, name );
  if( !sdr ) return;
  shader_destroy( sdr );
} // -------------------------------------------------------------------------

shader* shader_get( const char* name )
{
  return (shader*)hashtable_get( shader_manager, name );
} // -------------------------------------------------------------------------

b8 shader_add_uniform( shader* sdr, const char* uniform_name, u8 type )
{
  if( !sdr ) return false;
  gl_shader *id = (gl_shader*)sdr->internal_data;
  i32 location = glGetUniformLocation( id->program, uniform_name ); FZY_CHECK_GL_ERROR;
  if( location > -1 )
  {
    gl_uniform *u = memory_allocate( sizeof( struct gl_uniform ), MEM_TAG_SHADER );
    u->location = location;
    u->type = type;
    hashtable_set( id->uniforms, uniform_name, u );
    return true;
  }
  return false;
} // -------------------------------------------------------------------------

void shader_set_uniform( shader* sdr, const char*uniform_name, void* value )
{
  if( !sdr ) return;
  gl_shader* id = (gl_shader*)sdr->internal_data;
  gl_uniform *u = (gl_uniform*)hashtable_get( id->uniforms, uniform_name );

  if( !u ) return;

  switch( u->type )
  {
    case UNIFORM_TYPE_INT:
      glUniform1iv( u->location, 1, (i32*)value );
      return;

    case UNIFORM_TYPE_FLOAT:
      glUniform1fv( u->location, 1, (GLfloat*)value );
      return;

    case UNIFORM_TYPE_VEC2:
      glUniform2fv( u->location, 1, (GLfloat*)value );
      return;

    case UNIFORM_TYPE_VEC3:
      glUniform3fv( u->location, 1, (GLfloat*)value );
      return;

    case UNIFORM_TYPE_VEC4:
      glUniform4fv( u->location, 1, (GLfloat*)value );
      return;

    case UNIFORM_TYPE_MAT3:
      glUniformMatrix3fv( u->location, 1, GL_FALSE, (GLfloat*)value );
      return;

    case UNIFORM_TYPE_MAT4:
      glUniformMatrix4fv( u->location, 1, GL_FALSE, (GLfloat*)value );
      return;
  }
} // -------------------------------------------------------------------------

void shader_use( shader* sdr )
{
  if( !sdr ) return;
  gl_shader* id = (gl_shader*)sdr->internal_data;
  glUseProgram( id->program );
} // -------------------------------------------------------------------------


#endif // FZY_RENDERER_OPENGL
