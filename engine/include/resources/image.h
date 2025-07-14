#pragma once

#include "resources/resource_types.h"
/**
  @brief Loads an image using the stb library

  @param path - The path to the image file
  @return PTR - pointer to the image structure created
*/
image *image_create( const char* path );

/**
  @brief Frees resources used to load the image

  @param pic The image to destroy
*/
void image_destroy( image *pic );
