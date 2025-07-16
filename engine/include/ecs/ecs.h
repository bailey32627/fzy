#pragma once

#include "ecs/ecs_types.h"
/*
  @brief Initializes the entity component sytstem
*/
b8 ecs_initialize( void );

/*
  @brief Frees the memory associated with the ecs
*/
b8 ecs_shutdown( void );

/*
  @brief Creates an entity that is registered with the ecs system

  @return The created entity
*/
entity entity_create( void );

/*
  @brief Destroys the entity and signals that an entity was destroyed

  @param entity The entity that will be destroyed
*/
void entity_destroy( entity entity );

/*
  @brief Private - Registers a component to be used in the ecs, macro provided below
    for public use

  @param name The name of the component type
  @param type_size The size of the component type
*/
component_type_id component_register( const char* name, u32 type_size );

/*
  @brief Unregisters a component type from the ecs

  @param type_id - the id of the component to unregister
*/
void component_unregister( const char *name, component_type_id type_id );

/*
  @brief Adds the given component to the the provided entity

  @param entity The entity to attach the component to
  @param type_id the component type to add
  @returns a pointer to the added component
*/
void* component_add( entity entity, component_type_id type_id );

/*
  @brief Removes the component type from the entity

  @param entity The entity to remove the component from
  @param type_id - the id of the component type to remove
*/
void component_remove( entity entity, component_type_id type_id );

/*
  @brief Retrieves the component for the given entity

  @param entity The entity to get the component for
  @param type_id The type of component to retrieve
  @return Pointer to the component or 0
*/
void* component_get( entity entity, component_type_id type_id );

/*
  @brief Retrieves the type index for the component arrays

  @param type The component type to retrieve
  @return index of the component array
*/
u8 component_get_type_index( const char* type );

/*
  @brief Creates a process to operate on a group of entities

  @param signature The signature of the entities the process operates on
*/
process* process_create( signature signature );

/*
  Frees memory associated with the process

  @param process The process to destroy
*/
void process_destroy( process* process );

/*
  @brief Registers a process with the ECS

  @param name The name of the process being registered
  @param process Pointer to the process to register
*/
process_type_id process_register( const char* name, process* process );

/*
  @brief Unregisters a process and frees the memory

  @param name The name of the process to unregister
*/
void process_unregister( const char* name, process_type_id type_id );

/*
  @brief Retrieve the process from the ecs

  @param name The name of the process to retrieve
  @return Pointer to the process or 0 if not found
*/
process* process_get( process_type_id type_id );

process* process_get_by_name( const char *name );
