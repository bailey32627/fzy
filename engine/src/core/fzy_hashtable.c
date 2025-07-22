#include "core/fzy_hashtable.h"
#include "core/fzy_logger.h"
#include "core/fzy_string.h"
#include "core/fzy_mem.h"

#include <stdint.h>


//---------------------------------------------------------------------------------
// static Functions
// --------------------------------------------------------------------------------

static inline u64 fnv1a_hash64( const char *key )
{
  u64 hash = 1469598103934665603ULL; // offset basis
  while( *key )
  {
    hash ^= (uint8_t)(*key++);
    hash *= 1099511628211ULL; // FNV prime
  }
  return hash;
} // --------------------------------------------------------------------------

// -------------------------------------------------------------------------------
//  Structs
// -------------------------------------------------------------------------------
/** @brief Represents an entry in the hashtable */
typedef struct entry
{
  char name[MAX_NAME_LENGTH];
  u64 hash;
  u32 ref_count;
  void* data;
  struct entry* next;

} entry;
// ---------------------------------------------------------------------------

typedef struct hashtable_t
{
  entry** entries;
  u32 capacity;

} hashtable;
// ---------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Implementation
// ---------------------------------------------------------------------------------

hashtable *hashtable_create( u32 capacity )
{
  hashtable* table = memory_allocate( sizeof( struct hashtable_t ), MEM_TAG_HASHTABLE );
  table->capacity = capacity;
  table->entries = memory_allocate( sizeof( struct entry* ) * table->capacity, MEM_TAG_HASHTABLE );
  memory_set( table->entries, 0, sizeof( entry* ) * table->capacity );
  return table;
} // -------------------------------------------------------------------------

void hashtable_destroy( hashtable *table, void (*destroy_fn)(void*) )
{
  if( !table ) return;

  for( u32 i = 0; i < table->capacity; i++ )
  {
    entry* e = table->entries[ i ];
    while( e )
    {
      entry* next = e->next;
      if( e->data && destroy_fn )  destroy_fn( e->data );
      memory_delete( e, sizeof( struct entry ), MEM_TAG_HASHTABLE );
      e = next;
    }
  }

  memory_delete( table->entries, sizeof( entry*) * table->capacity, MEM_TAG_HASHTABLE );
  memory_delete( table, sizeof( hashtable ), MEM_TAG_HASHTABLE );
  table = NULL;
} // -------------------------------------------------------------------------

void hashtable_set( hashtable *table, const char *key, void* value )
{
  u64 hash = fnv1a_hash64( key );
  u32 bucket = hash % table->capacity;

  // check if exists ( update resource )
  for( entry* e = table->entries[ bucket ]; e; e = e->next )
  {
    if( e->hash == hash && string_is_equal( e->name, key ) )
    {
      e->ref_count++;
      return;
    }
  }

  // not found, create a new entry
  entry* entry = memory_allocate( sizeof( struct entry ), MEM_TAG_HASHTABLE );
  entry->hash = hash;
  string_copy( entry->name, 128, key );
  entry->data = value;
  entry->next = table->entries[ bucket ];
  table->entries[ bucket ] = entry;
  entry->ref_count = 1;
} // -------------------------------------------------------------------------

void *hashtable_get( hashtable *table, const char* key )
{
  u64 hash = fnv1a_hash64( key );
  u32 bucket = hash & ( table->capacity - 1 );

  for( entry *e = table->entries[ bucket ]; e; e = e->next )
  {
    if( e->hash == hash && string_is_equal( key, e->name ) )
    {
      e->ref_count += 1;
      return e->data;
    }
  }
  return NULL; // not found
} // -------------------------------------------------------------------------

void* hashtable_remove( hashtable* table, const char* key )
{
  u64 hash = fnv1a_hash64( key );
  u32 bucket = hash & (table->capacity - 1 );

  entry *prev = NULL;
  entry *e = table->entries[ bucket ];

  while( e )
  {
    if( e->hash == hash && string_is_equal( e->name, key ) )
    {
      e->ref_count -= 1;
      if( e->ref_count == 0 )
      {
        if( prev ) prev->next = e->next;
        else table->entries[ bucket ] = e->next;

        void* ret = e->data;
        memory_delete( e, sizeof( struct entry ), MEM_TAG_HASHTABLE );
        return ret;
      }
      return NULL;
    }
    prev = e;
    e = e->next; // advance
  }
  FZY_ERROR( "hashtable remove :: attempted to remove a non existing key" );
  return NULL;
} // -------------------------------------------------------------------------
