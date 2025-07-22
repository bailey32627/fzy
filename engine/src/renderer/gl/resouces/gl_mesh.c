#ifdef FZY_RENDERER_OPENGL

#include "renderer/resources/mesh.h"

#include "core/fzy_mem.h"
#include "core/fzy_hashtable.h"
#include "core/fzy_logger.h"

#include "renderer/gl/gl_types.h"

#include <stddef.h>

//----------------------------------------------------------------------------------
//  resource manager
// ---------------------------------------------------------------------------------
static hashtable *mesh_manager = NULL;
static b8 initialized = false;

//----------------------------------------------------------------------------------
// Structs
// ---------------------------------------------------------------------------------
/** @brief Represents a vertex buffer object and index buffer object used by opengl */
typedef struct gl_buffers
{
  u32 ibo;       // index buffer object
  u32 vbo;       // vertex buffer object
  u32 vao;       // vertex array object

} gl_buffers;
// ---------------------------------------------------------------------------


//----------------------------------------------------------------------------------
// Vertex buffer implementation
// ---------------------------------------------------------------------------------

static vertex_buffer* vertex_buffer_create( u32 vertex_quantity, u32 stride, b8 dynamic )
{
  vertex_buffer* vb = memory_allocate( sizeof( struct vertex_buffer ), MEM_TAG_MESH );

  vb->stride = stride;
  vb->vertex_quantity = vertex_quantity;
  vb->vertex_count = 0;
  vb->vertices = vector_create( stride, vb->vertex_quantity, MEM_TAG_MESH );

  vb->index_quantity = vertex_quantity * 3;
  vb->index_count = 0;
  vb->indices = vector_create( sizeof( u32 ), vb->index_quantity, MEM_TAG_MESH );

  vb->dirty = true;
  vb->internal_data = memory_allocate( sizeof( struct gl_buffers ), MEM_TAG_MESH );
  gl_buffers* id = vb->internal_data;
  id->vao = 0;
  id->vbo = 0;
  id->ibo = 0;

  // generate vao
  glGenVertexArrays( 1, &id->vao ); FZY_CHECK_GL_ERROR;
  glBindVertexArray( id->vao ); FZY_CHECK_GL_ERROR;

  // generate vbo
  glGenBuffers( 1, &id->vbo ); FZY_CHECK_GL_ERROR;
  glBindBuffer( GL_ARRAY_BUFFER, id->vbo );  FZY_CHECK_GL_ERROR;
  glBufferData( GL_ARRAY_BUFFER, vb->stride * vb->vertex_quantity, _vector_data( vb->vertices ), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );

  // generate ibo
  glGenBuffers( 1, &id->ibo ); FZY_CHECK_GL_ERROR;
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id->ibo ); FZY_CHECK_GL_ERROR;
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, vb->index_quantity * sizeof( u32 ), _vector_data( vb->indices ), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );

  switch( vb->stride )
  {
    case 56:
      glEnableVertexAttribArray(0); // position
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
      glEnableVertexAttribArray(1); // normal
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
      glEnableVertexAttribArray(2); // tangent
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tangent));
      glEnableVertexAttribArray(3); // bitangent
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, bitangent));
      glEnableVertexAttribArray(4); // texcoords
      glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texcoords));
      break;

    case 28:
      glEnableVertexAttribArray(0); // color
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, color));
      glEnableVertexAttribArray(2); // position
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, position));
      glEnableVertexAttribArray(3); // texcoords
      glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex2D), (void*)offsetof(vertex2D, texcoords));
      break;

    default:
      break;
  }
  glBindVertexArray( 0 );

  return vb;
} // --------------------------------------------------------------------------

static void vertex_buffer_add_vertices( vertex_buffer *vb, vector* verts, vector* indices )
{
  if( !vb ) return;

  u32 vs = vector_size( verts );
  u32 is = vector_size( indices );

  // copy the vertices into the vertex vector
  vector_fill( vb->vertices, _vector_data( verts ), vs, false );

  u32 idx;

  for( u32 i = 0; i < is; i++ )
  {
    idx = vb->vertex_count + *(vector_get( u32, indices, i ) );
    vector_push( vb->indices, &idx );
  }

  vb->vertex_count += vs;
  vb->index_count += is;

  vb->dirty = true;

} // --------------------------------------------------------------------------

static void vertex_buffer_upload( vertex_buffer* vb, b8 dynamic )
{
  if( !vb ) return;

  // update buffers
  if( vb->dirty )
  {
    gl_buffers* id = (gl_buffers*)vb->internal_data;

    //bind the vao
    glBindVertexArray( id->vao ); FZY_CHECK_GL_ERROR;

    glBindBuffer( GL_ARRAY_BUFFER, id->vbo ); FZY_CHECK_GL_ERROR;
    if( vb->vertex_count >= vb->vertex_quantity )
    {
      // update the quantity
      vb->vertex_quantity = vector_capacity( vb->vertices);
      // grow the vertex buffer
      glBufferData( GL_ARRAY_BUFFER, vb->stride * vb->vertex_quantity, _vector_data( vb->vertices ), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
    }
    else
    {
      glBufferSubData(GL_ARRAY_BUFFER, 0, vb->stride * vb->vertex_count, _vector_data(vb->vertices));
    }

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id->ibo ); FZY_CHECK_GL_ERROR;
    if( vb->index_count >= vb->index_quantity )
    {
      vb->index_quantity = vector_capacity( vb->indices );
      // grow openGL index buffer
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, vb->index_quantity * sizeof( u32 ), _vector_data( vb->indices ), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW );
    }
    else
    {
      glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, vb->index_count * sizeof( u32 ), _vector_data( vb->indices ) );
    }
    glBindVertexArray( 0 );
    vb->dirty = false;
  }
} // --------------------------------------------------------------------------

static void vertex_buffer_draw( vertex_buffer *vb, b8 dynamic )
{
  if( !vb ) return;
  gl_buffers* id = vb->internal_data;
  #ifdef FZY_CONFIG_DEBUG
    if( !id ) FZY_ERROR( "vertex_buffer_draw :: vertex buffer has no internal data" );
  #endif

  vertex_buffer_upload( vb, dynamic );

  glBindVertexArray( id->vao ); FZY_CHECK_GL_ERROR;
  u32 size = vector_size( vb->indices );

  glDrawElements( GL_TRIANGLES, size, GL_UNSIGNED_INT, 0 ); FZY_CHECK_GL_ERROR;
} // --------------------------------------------------------------------------

static void vertex_buffer_destroy( vertex_buffer* vb )
{
  if( !vb ) return;
  gl_buffers* id = vb->internal_data;
  #ifdef FZY_CONFIG_DEBUG
    if( !id ) FZY_ERROR( "vertex_buffer_destroy :: vertex buffer has no internal data" );
  #endif

  if( id->ibo )
  {
    glDeleteBuffers( 1, &id->ibo ); FZY_CHECK_GL_ERROR;
    id->ibo = 0;
  }
  if( id->vbo )
  {
    glDeleteBuffers( 1, &id->vbo ); FZY_CHECK_GL_ERROR;
    id->vbo = 0;
  }
  if( id->vao )
  {
    glDeleteVertexArrays( 1, &id->vao ); FZY_CHECK_GL_ERROR;
    id->vao = 0;
  }

  if( vb->vertices ) vector_destroy( vb->vertices );
  if( vb->indices ) vector_destroy( vb->indices );
  memory_delete( id, sizeof( struct gl_buffers ), MEM_TAG_MESH );
  memory_delete( vb, sizeof( struct vertex_buffer ), MEM_TAG_MESH );
} // --------------------------------------------------------------------------

static void mesh_destroy( mesh* mesh )
{
  if( !mesh ) return;
  if( mesh->buffer ) vertex_buffer_destroy( mesh->buffer );
  if( mesh->material ) material_remove( mesh->material->name );
  memory_delete( mesh, sizeof( struct mesh ), MEM_TAG_MESH );
}
//----------------------------------------------------------------------------------
// Mesh implementation
// ---------------------------------------------------------------------------------
void mesh_manager_initialize( void )
{
  if( initialized ) return;

  mesh_manager = hashtable_create( 2048 );
  initialized = true;
} // -------------------------------------------------------------------------

void mesh_manager_shutdown( void )
{
  if( !mesh_manager ) return;

  hashtable_destroy( mesh_manager, mesh_destroy );
  initialized = false;
  mesh_manager = NULL;
} // -------------------------------------------------------------------------

mesh* mesh_add( const char* name, u32 vertex_quantity, u32 vertex_stride, material *material, b8 dynamic )
{
  mesh* m = hashtable_get( mesh_manager, name );
  if( m ) return m;

  m = memory_allocate( sizeof( struct mesh ), MEM_TAG_MESH );
  m->buffer = vertex_buffer_create( vertex_quantity, vertex_stride, dynamic );
  m->material = material;

  // add it to the mesh_manager
  hashtable_set( mesh_manager, name, m );
  return m;
} // --------------------------------------------------------------------------

void mesh_remove( const char* name )
{
  mesh* m = hashtable_remove( mesh_manager, name );
  if( m )
    mesh_destroy( m );
} // --------------------------------------------------------------------------

mesh* mesh_get( const char* name )
{
  return (mesh*)hashtable_get( mesh_manager, name );
} // --------------------------------------------------------------------------

void mesh_set_vertices( mesh* mesh, vector* vertices, vector* indices )
{
  if( !mesh ) return;
  vector_fill( mesh->buffer->vertices, _vector_data( vertices ), vector_size( vertices ), true );
  vector_fill( mesh->buffer->indices, _vector_data( indices ), vector_size( indices ), true );
  mesh->buffer->dirty = true;

  mesh->buffer->vertex_quantity = vector_capacity(mesh->buffer->vertices );
  mesh->buffer->index_quantity = vector_capacity( mesh->buffer->indices );
  mesh->buffer->vertex_count = vector_size( mesh->buffer->vertices );
  mesh->buffer->index_count = vector_size( mesh->buffer->indices );
} // --------------------------------------------------------------------------

void mesh_add_vertices( mesh* mesh, vector* vertices, vector* indices )
{
  if( !mesh ) return;
  #ifdef FZY_CONFIG_DEBUG
    if( !vertices ) FZY_ERROR( "mesh_add_vertices :: vertices are NULL" );
    if( !indices ) FZY_ERROR( "mesh_add_vertices :: indices are NULL" );
  #endif // FZY_CONFIG_DEBUG

  vertex_buffer_add_vertices( mesh->buffer, vertices, indices );
  mesh->is_valid = false;
} // --------------------------------------------------------------------------

void mesh_draw( mesh* mesh, b8 dynamic )
{
  if( !mesh ) return;
  vertex_buffer_draw( mesh->buffer, dynamic );
} // --------------------------------------------------------------------------

#endif // FZY_RENDERER_OPENGL
