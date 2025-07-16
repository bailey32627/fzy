#include "ecs/ecs.h"
#include "core/fzy_logger.h"
#include "core/fzy_mem.h"
#include "core/fzy_queue.h"
#include "core/fzy_hashtable.h"

//----------------------------------------------------------------------------
//  entity tracking
//----------------------------------------------------------------------------
static signature entity_signatures[ MAX_ENTITIES ];  // tracks the signatures of the entities, attached components
static queue* entity_queue = NULL;  // queue to track avaliable entities
static u32 living_count = 0;    // tracks number of living entities

//----------------------------------------------------------------------------
//  component management
//----------------------------------------------------------------------------
static component_array *components[ MAX_COMPONENTS ];
static queue *component_types = 0;
static hashtable *component_registeration = 0;

//----------------------------------------------------------------------------
//  process management
//----------------------------------------------------------------------------
static process *processes[ MAX_PROCESSES ];    // track the processes being used
static queue* process_types = NULL;
static hashtable *process_registeration = 0;

//----------------------------------------------------------------------------
//  component helper functions
//----------------------------------------------------------------------------
// returns a pointer to the address in array memory
static inline void *array_offset( component_array *array, u32 idx )
{
  return (void*)((u8*)array->components + ( idx * array->type_size ));
} // -----------------------------------------------------------------------

static void unregister_component_type( void* t )
{
  memory_delete( t, sizeof( u8 ), MEM_TAG_COMPONENT );
} // ----------------------------------------------------------------------

static void unregister_process_type( void* t )
{
  memory_delete( t, sizeof( u8 ), MEM_TAG_PROCESS );
} // ----------------------------------------------------------------------

static component_array *component_array_create( u32 type_size )
{
  component_array *array = memory_allocate( sizeof( struct component_array ), MEM_TAG_COMPONENT );
  array->type_size = type_size;
  array->idx = 0;
  array->components = memory_allocate( type_size * MAX_ENTITIES, MEM_TAG_COMPONENT );

  memory_set( array->entity_to_index, -1, MAX_ENTITIES * sizeof( i32 ));
  memory_set( array->index_to_entity, -1, MAX_ENTITIES * sizeof( i32 ));
  return array;
} // ----------------------------------------------------------------

static void component_array_destroy( component_array *array )
{
  if( array )
  {
    memory_delete( array->components, array->type_size * MAX_ENTITIES, MEM_TAG_COMPONENT );
    memory_delete( array, sizeof( struct component_array ), MEM_TAG_COMPONENT );
    array = 0;
  }
} // ----------------------------------------------------------------

static void* component_array_add( component_array *array, entity entity )
{
  #ifdef FZY_CONFIG_DEBUG
    if( !array )
      FZY_ERROR( "component_array_insert :: array is null" );

    if( array->entity_to_index[ entity ] != -1 )
      FZY_WARNING( "component_array_insert :: assigning component to entity more than once" );
  #endif

  // Put new entry at end
  i32 newIndex = array->idx;
  array->entity_to_index[ entity ] = newIndex;
  array->index_to_entity[ newIndex ] = entity;
  void *a_idx = array_offset( array, newIndex );

  array->idx++;
  return a_idx;
} // ----------------------------------------------------------------

void component_array_remove( component_array *array, entity entity )
{
  #ifdef FZY_CONFIG_DEBUG
    if( !array )
      FZY_ERROR( "component_array_remove :: array is null" );
    if( array->entity_to_index[ entity ] == -1 )
      FZY_ERROR( "component_array_remove :: removing a non-existent component" );
  #endif

  // Copy element at end into deleted element's place to maintain density
  i32 remove_index = array->entity_to_index[ entity ];
  i32 last_index = array->idx - 1;
  memory_copy( array_offset( array, remove_index ), array_offset( array, last_index ), array->type_size );

  // Update map to point to moved spot
  i32 last = array->index_to_entity[ last_index ];
  array->entity_to_index[ last ] =  remove_index;
  array->index_to_entity[ remove_index ] = last;
  array->entity_to_index[ entity ] = -1;
  array->index_to_entity[ last_index ] = -1;

  if( array->idx > 0 )
    array->idx--;
} // ----------------------------------------------------------------

void* component_array_get( component_array *array, entity entity )
{
  #ifdef FZY_CONFIG_DEBUG
    if( array->entity_to_index[ entity ] == -1 )
      FZY_ERROR( "component_array_get :: retrieving non-existent component" );
  #endif

  return array_offset( array, array->entity_to_index[ entity ] );
} // ----------------------------------------------------------------

void process_entity_signature_changed( entity entity, signature signature )
{
  for( u8 i = 0; i < MAX_PROCESSES; i++ )
  {
    if( processes[ i ] )
    {
      if ((signature & processes[i]->signature) == processes[i]->signature)
      {
        vector_push( processes[ i ]->entities, &entity );
      }
      else
      {
        vector_remove( processes[ i ]->entities, &entity );
      }
    }
  }
} // ------------------------------------------------------------------

//----------------------------------------------------------------------------
//  Implementation
//----------------------------------------------------------------------------

b8 ecs_initialize( void )
{
  if( entity_queue || component_types || process_types ) return false;

  // create queues
  entity_queue = queue_create( entity, MAX_ENTITIES, MEM_TAG_ENTITY );
  component_types = queue_create( u8, MAX_COMPONENTS, MEM_TAG_COMPONENT );
  process_types = queue_create( u8, MAX_PROCESSES, MEM_TAG_PROCESS );

  // create hashtables
  component_registeration = hashtable_create( MAX_COMPONENTS + 7, unregister_component_type );
  process_registeration = hashtable_create( MAX_COMPONENTS + 7, unregister_process_type );

  for( u16 i = 0; i < MAX_ENTITIES; i++ )
  {
    queue_push( entity_queue, &i );
    entity_signatures[ i ] = 0;

    if( i < MAX_COMPONENTS )
    {
      queue_push( component_types, &i );
      components[ i ] = NULL;
    }
    if( i < MAX_PROCESSES )
    {
      queue_push( process_types, &i );
      processes[ i ] = NULL;
    }
  }
  return true;
} // --------------------------------------------------------------------------

b8 ecs_shutdown( void )
{
  if( entity_queue )
  {
    queue_destroy( entity_queue );
    entity_queue = 0;
  }
  if( component_types )
  {
    queue_destroy( component_types );
    component_types = 0;
  }

  if( component_registeration )
  {
    hashtable_destroy( component_registeration );
    component_registeration = 0;
  }

  for( u8 i = 0; i < MAX_COMPONENTS; i++ )
    if( components[ i ] )
      component_array_destroy( components[ i ] );

  if( process_types )
  {
    queue_destroy( process_types );
    process_types = 0;
  }

  if( process_registeration )
  {
    hashtable_destroy( process_registeration );
    process_registeration = 0;
  }

  for( u8 i = 0; i < MAX_PROCESSES; i++ )
    if( processes[ i ] )
      process_destroy( processes[ i ] );

  if( entity_queue || component_types || process_types )
    return false;

  return true;
} // --------------------------------------------------------------------------

entity entity_create( void )
{
  if( living_count < MAX_ENTITIES )
  {
    entity e = *((entity*)queue_get_front( entity_queue ) );
    queue_pop( entity_queue );
    living_count++;
    return e;
  }
  FZY_ERROR( "entity_create :: to many entities exist" );
  return MAX_ENTITIES;
} // --------------------------------------------------------------------------

void entity_destroy( entity entity )
{
  if( entity > MAX_ENTITIES )
  {
    FZY_ERROR( "entity_distroy :: attempted to destroy an out of range entity!!!" );
  }

  entity_signatures[ entity ] = 0;
  queue_push( entity_queue, &entity );
  living_count--;

  // remove entity reference from components array
  for( u8 i = 0; i < MAX_COMPONENTS; i++ )
  {
    if( components[ i ] )
    {
      component_array_remove( components[ i ], entity );
    }
  }

  // remove entity reference from the systems
  for( u8 i = 0; i < MAX_PROCESSES; i++ )
  {
    if( processes[ i ] )
      vector_remove( processes[ i ]->entities, &entity );
  }
} // --------------------------------------------------------------------------

component_type_id component_register( const char* name, u32 type_size )
{
  if( queue_is_empty( component_types ) )
    FZY_ERROR( "component_register :: too many components are registered" );

  u8* rt = hashtable_get( component_registeration, name );
  if( rt != 0 )
    FZY_ERROR( "component_register :: type is already registered" );

  rt = memory_allocate( sizeof( u8 ), MEM_TAG_COMPONENT );
  *rt = *((u8*)queue_get_front( component_types ));
  hashtable_set( component_registeration, name, rt );

  components[ *rt ] = component_array_create( type_size );
  return *rt;
} // --------------------------------------------------------------------------

void component_unregister( const char *name, component_type_id type_id )
{
  u8* rt = hashtable_get( component_registeration, name );
  if( rt )
  {
    if( *rt != type_id ) FZY_ERROR( "component_unregister :: typeid / registered type mismatch");
    hashtable_remove( component_registeration, name );
    queue_push( component_types, rt );
    if( components[ *rt ] )
    {
      component_array_destroy( components[ *rt ] );
    }
  }
} // --------------------------------------------------------------------------

void* component_add( entity entity, component_type_id type_id )
{
  if( components[ type_id ] && entity < MAX_ENTITIES )
  {
    void *cmpt = component_array_add( components[ type_id ], entity );
    entity_signatures[entity] = signature_set( entity_signatures[ entity ], type_id );
    process_entity_signature_changed( entity, entity_signatures[ entity ] );
    return cmpt;
  }
  return NULL;
} // --------------------------------------------------------------------------

void component_remove( entity entity, component_type_id type_id )
{
  if( components[ type_id ] && entity < MAX_ENTITIES )
  {
    component_array_remove( components[ type_id ], entity );
    entity_signatures[ entity ] = signature_remove( entity_signatures[ entity ], type_id );
    process_entity_signature_changed( entity, entity_signatures[ entity ] );
    return;
  }
} // --------------------------------------------------------------------------

void* component_get( entity entity, component_type_id type_id )
{
  if( components[ type_id ] )
  {
    return component_array_get( components[ type_id ], entity );
  }
  return NULL;
} // --------------------------------------------------------------------------

process* process_create( signature signature )
{
  process *s = memory_allocate( sizeof( struct process ), MEM_TAG_PROCESS );
  s->entities = vector_create( sizeof( entity ), 64, MEM_TAG_PROCESS );
  s->signature = signature;
  s->update_fn = 0;
  return s;
} // --------------------------------------------------------------------------

void process_destroy( process* process )
{
  if( process )
  {
    if( process->entities )
      vector_destroy( process->entities );
    memory_delete( process, sizeof( struct process ), MEM_TAG_PROCESS );
    process = 0;
  }
} // --------------------------------------------------------------------------

process_type_id process_register( const char* name, process* process )
{
  if( queue_is_empty( process_types ) )
   FZY_ERROR( "process_register :: too many systems are registered" );

 u8* rt = hashtable_get( process_registeration, name );
 if( rt != 0 )
   FZY_ERROR( "process_register :: process is already registered" );

  rt = memory_allocate( sizeof( u8 ), MEM_TAG_PROCESS );
  *rt = *((u8*)queue_get_front( process_types ));
  hashtable_set( process_registeration, name, rt );

  processes[ *rt ] = process;
  return *rt;
} // --------------------------------------------------------------------------

void process_unregister( const char* name, process_type_id type_id )
{
  u8* rt = hashtable_get( process_registeration, name );
  if( rt )
  {
    hashtable_remove( process_registeration, name );
    queue_push( process_types, rt );
    if( processes[ *rt ] )
    {
      process_destroy( processes[ *rt ] );
      processes[ *rt ] = 0;
    }
  }
} // --------------------------------------------------------------------------

process* process_get( process_type_id type_id )
{
  if( processes[ type_id ] )
    return processes[ type_id ];
  return NULL;
} // --------------------------------------------------------------------------

process* process_get_by_name( const char *name )
{
  u8 *rt = hashtable_get( process_registeration, name );
  if( rt )
    return processes[ *rt ];
  return NULL;
} // --------------------------------------------------------------------------
