#pragma once

#include "defines.h"
#include "renderer/resources/material.h"
#include "core/fzy_vector.h"


//---------------------------------------------------------------------------
// Structs
// --------------------------------------------------------------------------
/** @brief Represents a 3D point in the engine */
typedef struct vertex
{
  vec3 position;   // 12 bytes
  vec3 normal;     // 12 bytes
  vec3 tangent;    // 12 bytes
  vec3 bitangent;  // 12 bytes
  vec2 texcoords;  // 8 bytes

} vertex;
// ----------------------------------------------------------------------------

/** @brief Represents a 2D vertex in the engine */
typedef struct vertex2D
{
  vec3 color;     // 12 bytes
  vec2 position;  // 8 bytes
  vec2 texcoords; // 8 bytes

} vertex2D;
// ----------------------------------------------------------------------------

/** @brief Represents a vertex buffer object in the engine */
typedef struct vertex_buffer
{
  vector* vertices;    // holds the vertices of the buffer
  vector* indices;     // holds the indices of the buffer
  u32 stride;          // holds the stride of the vertices
  u32 vertex_quantity; // holds the number of vertices in the buffer
  u32 vertex_count;    // the number of vertices in the vertex buffer
  u32 index_quantity;  // hold the max number of indices
  u32 index_count;     // holds the number of indices in the buffer
  b8 dirty;            // indicates if the buffer needs to be reloaded
  void *internal_data; // data maintained by the backeend renderer

} vertex_buffer;
// ----------------------------------------------------------------------------

/** @brief Represents a basic geometry in the engine */
typedef struct mesh
{
  char name[ MAX_NAME_LENGTH ];  // name of the mesh resource
  vertex_buffer *buffer;         // the vertex buffer to render the mesh
  material *material;            // the material to apply to the mesh
  b8 is_valid;                   // indicates that the mesh is ready to render

} mesh;
// ----------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Vertex_buffer definations
// -------------------------------------------------------------------------------

/**
  @brief Initializes the mesh manager for the engine
*/
void mesh_manager_initialize( void );

/**
  @brief Shutsdown the mesh manager and frees the meshes held within
*/
void mesh_manager_shutdown( void );

/**
  @brief Creates or references a mesh in the manaager

  @param name - the name of the mesh to add
  @param quantity - the number of vertices to initialize the mesh with
  @param stride - the stride of the vertices held in the vertex buffer
  @param material - the material to apply to the mesh
  @param dynamic - hint to backend for usage
*/
FZY_API mesh* mesh_add( const char* name, u32 vertex_quantity, u32 vertex_stride, material *material, b8 dynamic );

/**
  @brief Removes a mesh if all references are 0

  @brief name - the name of the mesh to remove
*/
FZY_API void mesh_remove( const char* name );

/**
  @brief Gets a reference to a mesh

  @param name - the name of the mesh to get
*/
FZY_API mesh* mesh_get( const char* name );

/**
  @brief Sets the vertices for this mesh, this will replace all vertices in the mesh

  @param mesh - the mesh to set the vertices for
  @param vertices - the array of vertices to set in the mesh
  @param indices - the array of indices indicating how to draw the vertices
*/
FZY_API void mesh_set_vertices( mesh* mesh, vector* vertices, vector* indices );

/**
  @brief adds the vertices to the mesh

  @param mesh - the mesh to add the vertex to
  @param vertices - the vertices to add to the mesh
  @param indices - the indices to add to the mesh
*/
FZY_API void mesh_add_vertices( mesh* mesh, vector* vertices, vector* indices );

/**
  @brief Draws the mesh
  @param mesh - the mesh to draw
  @param dynamic - hint for usage
*/
FZY_API void mesh_draw( mesh* mesh, b8 dynamic );
