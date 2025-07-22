#include "renderer/image.h"

#include "core/fzy_mem.h"
#include "core/fzy_logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

image* image_create( const char* path )
{
  image *img = memory_allocate( sizeof( struct image ), MEM_TAG_TEXTURE );
  img->pixels = NULL;

  img->pixels = stbi_load( path, &img->width, &img->height, &img->channels, 0 );

  if( !img->pixels )
  {
    FZY_WARNING( "image_create :: unable to load image from path [ %s ]", path );
    image_destroy( img );
    return NULL;
  }
  return img;
} // ------------------------------------------------------------------------------

void image_destroy( image* img )
{
  if( !img ) return;

  if( img->pixels )
  {
    stbi_image_free( img->pixels );
    img->pixels = NULL;
  }
  memory_delete(  img, sizeof( struct image ), MEM_TAG_TEXTURE );
  img = NULL;
} // ------------------------------------------------------------------------------
