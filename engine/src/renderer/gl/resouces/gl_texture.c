#include "renderer/resources/texture.h"
#include "renderer/image.h"

#include "core/fzy_hashtable.h"
#include "core/fzy_mem.h"
#include "core/fzy_logger.h"

#include "renderer/gl/gl_types.h"

//---------------------------------------------------------------------------------
// structs
// --------------------------------------------------------------------------------
/** Represents a texture in opengl */
typedef struct gl_texture
{
  u32 id;             // opengl texture id
  u32 format;         // opengl pixel format
  i32 width;          // width of the texture
  i32 height;         // height of the texture
  u32 channels;       // the number of color channels used in the texture
  u32 atlas_square;   // number of textures held by the atlas, must be a square
  u8 type;            // hold the type of the texture

} gl_texture;
// ---------------------------------------------------------------------------


//---------------------------------------------------------------------------------
// manager
// --------------------------------------------------------------------------------

static hashtable* texture_manager = NULL;
static b8 initialized = false;

//---------------------------------------------------------------------------------
// static funcitons
// --------------------------------------------------------------------------------
static void texture_destroy( texture* tex )
{
  if( !tex ) return;

  gl_texture* id = (gl_texture*)tex->internal_data;
  if( id->type == ATTACHMENT_DEPTH )
  {
    if( id->id != 0 )
    {
      glDeleteRenderbuffers( 1, &id->id );
      id->id = 0;
    }
  }
  else
  {
    if( id->id != 0 )
    {
      glDeleteTextures( 1, &id->id );
      id->id = 0;
    }
  }
  memory_delete( id, sizeof( struct gl_texture ), MEM_TAG_TEXTURE );
  memory_delete( tex, sizeof( struct texture ), MEM_TAG_TEXTURE );
  glBindTexture(GL_TEXTURE_2D, 0);
} // -------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// implemenation
// --------------------------------------------------------------------------------

void texture_manager_initialize( void )
{
  if( initialized ) return;

  texture_manager = hashtable_create( 128 );
  initialized = true;
} // ------------------------------------------------------------------------

void texture_manager_shutdown( void )
{
  if( !texture_manager ) return;

  hashtable_destroy( texture_manager, texture_destroy );
  initialized = false;
  texture_manager = NULL;
} // ------------------------------------------------------------------------

texture* texture_add( const char *name, const char* path, u32 atlas_square )
{
  texture *t = hashtable_get( texture_manager, name );
  if( t ) return t;

  image* img = image_create( path );
  if( !img || img->channels < 3 || img->channels > 4 )
  {
    FZY_WARNING( "gl_texture_add :: failed to create image at [ %s ]", path );
    return NULL;
  }

  t = memory_allocate( sizeof( struct texture ), MEM_TAG_TEXTURE );
  t->internal_data = memory_allocate( sizeof( struct gl_texture ), MEM_TAG_TEXTURE );
  gl_texture* id = t->internal_data;
  id->id = 0;
  id->atlas_square = atlas_square;
  id->width = img->width;
  id->height = img->height;
  id->format = img->channels == 3 ? GL_RGB : GL_RGBA;

  glGenTextures( 1, &id->id ); FZY_CHECK_GL_ERROR;
  glBindTexture( GL_TEXTURE_2D, id->id ); FZY_CHECK_GL_ERROR;

  glTexImage2D( GL_TEXTURE_2D, 0, id->format, id->width, id->height, 0, id->format, GL_UNSIGNED_BYTE, img->pixels );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); FZY_CHECK_GL_ERROR;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); FZY_CHECK_GL_ERROR;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); FZY_CHECK_GL_ERROR;
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ); FZY_CHECK_GL_ERROR;
  glGenerateMipmap( GL_TEXTURE_2D ); FZY_CHECK_GL_ERROR;
  glBindTexture( GL_TEXTURE_2D, 0 ); FZY_CHECK_GL_ERROR;
  image_destroy( img );
  id->type = ATTACHMENT_COLOR;

  hashtable_set( texture_manager, name, t );
  return t;
} // ------------------------------------------------------------------------

texture* texture_create_writeable( u8 attachment, u16 width, u16 height )
{
  if( attachment >= ATTACHMENT_TOTAL ) return NULL;

  texture *tex = memory_allocate( sizeof( struct texture ), MEM_TAG_TEXTURE );
  tex->internal_data = memory_allocate( sizeof( struct gl_texture ), MEM_TAG_TEXTURE );
  gl_texture* id = (gl_texture*)tex->internal_data;

  switch( attachment )
  {
    case ATTACHMENT_POSITION:
      id->width = width;
      id->height = height;
      id->channels = 3;
      id->format = GL_RGB16F;
      id->atlas_square = 1;
      id->type = attachment;
      // generate texture for the position
      glGenTextures( 1, &id->id );
      glBindTexture( GL_TEXTURE_2D, id->id );
      glTexImage2D( GL_TEXTURE_2D, 0, id->format, id->width, id->height, 0, GL_RGB, GL_FLOAT, 0 );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      break;

    case ATTACHMENT_NORMAL:
      id->width = width;
      id->height = height;
      id->channels = 3;
      id->format = GL_RGB16F;
      id->atlas_square = 1;
      id->type = attachment;
      // generate texture for the normals
      glGenTextures( 1, &id->id );
      glBindTexture( GL_TEXTURE_2D, id->id );
      glTexImage2D( GL_TEXTURE_2D, 0, id->format, id->width, id->height, 0, GL_RGB, GL_FLOAT, 0 );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      break;

    case ATTACHMENT_COLOR:
      id->width = width;
      id->height = height;
      id->channels = 4;
      id->format = GL_RGBA;
      id->atlas_square = 1;
      id->type = attachment;
      // generate texture for the albedo
      glGenTextures( 1, &id->id );
      glBindTexture( GL_TEXTURE_2D, id->id );
      glTexImage2D( GL_TEXTURE_2D, 0, id->format, id->width, id->height, 0, GL_RGBA, GL_FLOAT, 0 );
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); FZY_CHECK_GL_ERROR;
      break;

    case ATTACHMENT_DEPTH:
      id->width = width;
      id->height = height;
      id->channels = 0;
      id->format = 0;
      id->atlas_square = 1;
      id->type = attachment;
      // generate the depth buffer
      glGenRenderbuffers( 1, &id->id );
      glBindRenderbuffer( GL_RENDERBUFFER, id->id );
      glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height );
      glBindRenderbuffer( GL_RENDERBUFFER, 0 );
      break;

    default:
      break;
  }
  return tex;
} // ------------------------------------------------------------------------

void texture_destroy_writeable( texture* tex )
{
  texture_destroy( tex );
} // -------------------------------------------------------------------------

void texture_remove( const char* name )
{
  texture* tex = hashtable_remove( texture_manager, name );
  if( tex ) texture_destroy( tex );
} // ------------------------------------------------------------------------

void texture_bind( texture *texture, u32 active_texture )
{
  if( !texture )
  {
    #ifdef FZY_CONFIG_DEBUG
     FZY_ERROR( "gl_texture_bind :: texture is null" );
    #endif
    return;
  }
  gl_texture* id = (gl_texture*)texture->internal_data;

  glActiveTexture( GL_TEXTURE0 + active_texture ); FZY_CHECK_GL_ERROR;
  glBindTexture( GL_TEXTURE_2D, id->id ); FZY_CHECK_GL_ERROR;
} // ------------------------------------------------------------------------

void texture_unbind( void )
{
  glBindTexture( GL_TEXTURE_2D, 0 ); FZY_CHECK_GL_ERROR;
} // ------------------------------------------------------------------------
