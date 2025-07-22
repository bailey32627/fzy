#pragma once

#include "defines.h"

//----------------------------------------------------------------------------------
// structs
// ---------------------------------------------------------------------------------

/**  @brief Represents the texture attachments for a frame buffer  */
typedef enum attachment
{
  ATTACHMENT_POSITION = 0,
  ATTACHMENT_NORMAL,
  ATTACHMENT_COLOR,
  ATTACHMENT_DEPTH,
  ATTACHMENT_TOTAL

} attachment;
// -------------------------------------------------------------------------

/** @brief Represents a generic texture */
typedef struct texture
{
  char name[ MAX_NAME_LENGTH ];  // Name of the texture
  void *internal_data;          // data maintained by the backend

} texture;
// ----------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// definations
// --------------------------------------------------------------------------------

/**
  @brief Initializes the texture manager
*/
void texture_manager_initialize( void );

/**
  @brief Shuts down the texture manager and frees the texture resources
*/
void texture_manager_shutdown( void );

/**
  @brief Creates a texture on the backend

  @param path The path the texture file
  @param atlas_square The number of rows and columns in the atlas
  @return Pointer to the new generic texture
*/
texture* texture_add( const char *name, const char* path, u32 atlas_square );

/*
  @brief Creates a writeable texture that is empty

  @param attachment The type of attachment this texture will be
  @param width The width of the texture
  @param height The height of the texture
  @return Pointer to the new texture
*/
texture* texture_create_writeable( u8 attachment, u16 width, u16 height );
void texture_destroy_writeable( texture* tex );
/**
  @brief Removes a texture from the manager and frees it if reference reaches 0

  @param name - the name of the texture to remove
*/
void texture_remove( const char* name );

/**
  @brief Binds the texture for rendering

  @param texture - the texture to bind
  @param active_texture - the texture location to bind to
*/
void texture_bind( texture *texture, u32 active_texture );

/**
  @brief Unbinds all textures
*/
void texture_unbind( void );
