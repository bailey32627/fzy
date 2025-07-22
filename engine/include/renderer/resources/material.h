#pragma once

#include "defines.h"
#include "renderer/resources/texture.h"

/** @brief Represents a material, texture and lighting, for a mesh */
typedef struct material
{
  char name[ MAX_NAME_LENGTH ];  // name of the material
  texture *albedo;      // color texture to apply
  texture *normal;      // normal map to apply
  u32 albedo_index;     // index to the albedo texture in a texture atlas
  u32 normal_index;     // index to the normal texture in the texture atlas
  f32 reflectivity;     // 0-1 value indicating the reflectivity of teh material

} material;
// ----------------------------------------------------------------------------

/**
  @brief Initializes the manager, called on initialization of the engine
*/
void material_manager_initialize( void );

/**
  @brief Shuts down the material manager and frees all resources
*/
void material_manager_shutdown( void );

/**
  @brief Creates a material for rendering

  @param albedo - The texture to apply
  @param albedo_index - index into the texture atlas, pass 0 or 1 if not an atlas
  @param normal_map - The nomral map to apply or 0 if not used
  @param normal_index - index into the texture atlas holding the normal map or 1, 0 if not used
  @param reflectivity - The reflectivity of the material
*/
material* material_add( const char* name, texture* albedo, u32 albedo_index, texture* normal_map, u32 normal_index, f32 reflectivity );

/**
  @brief Removes a material reference, frees at 0

  @param name - the name of the material to remove
*/
void material_remove( const char* name );

/**
  @brief Gets a reference to the material with the name

  @return ptr - Pointer to the resource
*/
material* material_get( const char* name );
