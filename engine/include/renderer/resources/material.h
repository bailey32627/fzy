#pragma once

#include "defines.h"

/** @brief Represents a material, texture and lighting, for a mesh */
typedef struct material
{
  char name[ MAX_NAME_LENGTH ];  // name of the material
  //texture *albedo;      // color texture to apply
  //texture *normal;      // normal map to apply
  u32 albedo_index;     // index to the albedo texture in a texture atlas
  u32 normal_index;     // index to the normal texture in the texture atlas
  f32 reflectivity;     // 0-1 value indicating the reflectivity of teh material

} material;
// ----------------------------------------------------------------------------


void material_remove( const char* name );
