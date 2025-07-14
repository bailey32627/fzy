#pragma once

#ifdef FZY_RENDERER_OPENGL

#include "defines.h"
#include "resources/resource_types.h"

/**
  @brief Creates a vertex buffer object for opengl

  @param vb The vertex buffer to create resources for
  @return true if successfully created, false otherwise
*/
b8 gl_vertex_buffer_create( vertex_buffer* vb );

/**
  @brief Frees the backend resources held by the vertex buffer

  @param vb The vertex buffer to destroy backend resources of
  @return true if successful
*/
b8 gl_vertex_buffer_destroy( vertex_buffer *vb );

/**
  @brief Pushes the vertex buffer data to the GPU

  @param vb The vertex buffer to load
  @param dynamic Indicates if the vbo should be dynamic or static
*/
void gl_vertex_buffer_upload( vertex_buffer *vb, b8 dynamic );

/**
  @brief Creates the internal resources for a mesh

  @returns true if successful
*/
b8 gl_mesh_create( mesh* mesh );

/**
  @brief Frees all the resources associated with the mesh

  @param mesh The geometry to destroy
  @return True if successful
*/
b8 gl_mesh_destroy( mesh* mesh );

/**
  @brief Uploads the mesh to the backend

  @param mesh The mesh to upload
  @param dynamic Indicates if the mesh is dynamic
*/
void gl_mesh_upload( mesh* mesh, b8 dynamic );

/**
  @brief Update the buffers for the mesh

  @param mesh The mesh to update
*/
void gl_mesh_update( mesh* mesh );

/**
  @brief Draw commands for opengl

  @param mesh The geometry to draw
*/
void gl_mesh_draw( mesh* mesh );

#endif // FZY_RENDERER_OPENGL
