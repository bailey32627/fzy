#pragma once

#include "defines.h"
#include "renderer/resources/resource_types.h"

// --------------------------------------------------------------------------------
// Shaders
// --------------------------------------------------------------------------------
/**
  @brief Initializes the shader manager that ensure each shader is only initialized once
*/
void shader_manager_initialize( void );

/**
  @brief Shutdown the shader manager and esure that all the shaders are freed
*/
void shader_manager_shutdown( void );

/**
  @brief creates an shader and allocates backend resources

  @param name - the name for the shader in the resource manager
  @param vertex_source Source code for the vertex shader ( Required )
  @param fragment_source Source code for the fragment shader ( Required )
  @return Pointer to the new shader
*/
FZY_API shader* shader_add( const char *name, const char* vertex_source, const char* fragment_source );

/**
  @brief Frees the shader and the backend resources

  @param shader The shader to free resources for
*/
FZY_API void shader_remove( const char* name );

/**
  @brief Retrieves a shader by name and adds a reference to it

  @param name - The name of the shader
  @return pointer - pointer to the shader or NULL if not found
*/
FZY_API shader* shader_get( const char* name );

/**
  @brief Add a uniform to the uniforms table in the shader

  @param shader The shader to add uniform to
  @param name The name of the uniform
  @param type The uniform type
  @return True if successful, false otherwise
*/
FZY_API b8 shader_add_uniform( shader* sdr, const char* uniform_name, u8 type );

/**
  @brief Sets the value of the uniform with the given name

  @param sdr The shader to access
  @param name The name of the uniform
  @param value Pointer to the value to copy to the uniform
*/
FZY_API void shader_set_uniform( shader* sdr, const char* uniform_name, void* value );

/**
  @brief Tells the backend to bind this shader

  @param shader The shader to bind, 0 to unbind
*/
FZY_API void shader_use( shader* sdr );
