#pragma once

#include "defines.h"

/**
  @brief Represents a hashtable for fast lookups, uses chaining for
      collision resolution
*/
typedef struct hashtable_t hashtable;


/**
  @brief Creates a new hashtable and returns a pointer to it
  @param capacity The initialize size of the table
  @param memory_tag The memory scope to assign this table to
  @param destroy_func Function to free memory held in the table
  @return Pointer to the hashtable
*/
FZY_API hashtable *hashtable_create( u32 capacity );

/**
  @brief Frees the hashtable, has ability to provide a free function for the
    data stored in the table
  @param table - The table to be freed
  @param destroy_fn - the function to destroy any entities
*/
FZY_API void hashtable_destroy( hashtable *table, void (*destroy_fn)(void*) );

/**
  @brief Sets the resource at the key, to the value

  @param table - The table to access
  @param key - the key to the item
  @param value - the value to set the resource to
  @return u64 - hash value to the resource
*/
FZY_API void hashtable_set( hashtable *table, const char *key, void* value );

/**
  @brief Retrieve the value stored at the key in the hashtable, will increament the reference count
  @param table - the hashtabel to access
  @param key - the key to access
  @return Ptr - pointer to the element at the key
*/
FZY_API void *hashtable_get( hashtable *table, const char* key );

/**
  @brief Removes the value at the key and returns it, will decrement the reference count
    sets the value at the key to null
  @param table - The table to access
  @param key - the key to remove
*/
FZY_API void* hashtable_remove( hashtable* table, const char* key );
