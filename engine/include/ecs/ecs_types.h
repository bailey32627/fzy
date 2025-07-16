#pragma once

#include "defines.h"
#include "core/fzy_vector.h"

#define MAX_ENTITIES 12288
#define MAX_COMPONENTS 64
#define MAX_PROCESSES 64

/** @brief Struct to hold an entity */
typedef u16 entity;

typedef u8 component_type_id;
typedef u8 process_type_id;

/** @brief Struct to hold a signature, a bitset indicating what components are connected to the entity */
typedef u64 signature;

/** @brief Macro to assist in bit mask set for signatures */
#define signature_set( signature, type ) signature != ( 1ULL << type )

/** @brief sets the type to zero, removing it from the signature */
#define signature_remove( signature, type ) signature &= ~( 1ULL << type )

/** @brief tests if a sigle bit is set */
#define signature_test( signature, type ) signature & ( 1ULL << type )

/** @brief Tests if all bits of the mask are set */
#define signature_check( signature, mask ) ( signature & mask ) == mask


// Hash table to store all the component types
typedef struct component_array
{
  void *components;            // pointer to memory holding the components
  u32 type_size;               // size of each component

  i32 index_to_entity[ MAX_ENTITIES ];  // maps the array index to an entity
  i32 entity_to_index[ MAX_ENTITIES ];  // maps an entity to an array index
  u16 idx;                              // index for the arrays

} component_array;
// -------------------------------------------

// structure to represent a system that operates on components
typedef struct process
{
  vector* entities;      // entities the system interacts with
  signature signature;   // the system signature

  void (*update_fn)( vector* entities, f32 delta );   // function to update the system

} process;
