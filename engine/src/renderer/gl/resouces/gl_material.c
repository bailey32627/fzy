#ifdef FZY_RENDERER_OPENGL

#include "renderer/resources/material.h"
#include "core/fzy_mem.h"
#include "core/fzy_hashtable.h"
#include "core/fzy_math.h"


static hashtable* material_manager = NULL;
static b8 initialized = false;

//--------------------------------------------------------------------------------
// static functions
// -------------------------------------------------------------------------------

static void material_destroy( material* mtl )
{
  if( !mtl ) return;
  if( mtl->albedo ) texture_remove( mtl->albedo->name );
  if( mtl->normal ) texture_remove( mtl->normal->name );

  memory_delete( mtl, sizeof( struct material ), MEM_TAG_MATERIAL );
  mtl = NULL;
} // -------------------------------------------------------------------------


void material_manager_initialize( void )
{
  if( initialized ) return;
  material_manager = hashtable_create( 512 );
  initialized = true;
} // ------------------------------------------------------------------------

void material_manager_shutdown( void )
{
  if( !material_manager ) return;
  hashtable_destroy( material_manager, material_destroy );
  initialized = false;
  material_manager = NULL;
} // ------------------------------------------------------------------------

material* material_add( const char* name, texture* albedo, u32 albedo_index, texture* normal_map, u32 normal_index, f32 reflectivity )
{
  material* mtl = hashtable_get( material_manager, name );
  if( mtl ) return mtl;

  mtl = memory_allocate( sizeof( struct material ), MEM_TAG_MATERIAL );
  if( albedo )
  {
    mtl->reflectivity = (f32)(clamp( reflectivity, 0.0, 1.0 ));
    mtl->albedo = albedo;
    mtl->albedo_index = albedo_index <= 1 ? 1 : albedo_index;
  }
  if( normal_map )
  {
    mtl->normal = normal_map;
    mtl->normal_index = normal_index <= 1 ? 1 : normal_index;
  }

  hashtable_set( material_manager, name, mtl );
  return mtl;
} // ------------------------------------------------------------------------

void material_remove( const char* name )
{
  material* mtl = hashtable_remove( material_manager, name );
  if( mtl ) material_destroy( mtl );
} // ------------------------------------------------------------------------

material* material_get( const char* name )
{
  return (material*)hashtable_get( material_manager, name );
} // ------------------------------------------------------------------------

#endif // FZY_RENDERER_OPENGL
