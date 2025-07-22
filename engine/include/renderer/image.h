#pragma once

#include "defines.h"

/**
  @brief Represents an image loaded from stb_lib
*/
typedef struct image
{
  i32 width;      // holds the width of the image
  i32 height;     // holds the height of the image
  i32 channels;   // holds the number of channels used for the image
  u8 *pixels;     // hold the array of pixels for the image

} image;
// -----------------------------------------------------------------------



/*
  @brief Loads an image using the stb library

  @param path The path the image file
  @return Pointer to the image structure created
*/
image *image_create( const char *path );

/*
  @brief Frees resources used to load the image

  @param pic The image to destroy
*/
void image_destroy( image *pic );
