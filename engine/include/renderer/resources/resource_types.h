#pragma once

#include "defines.h"
#include "core/fzy_vector.h"


#define ASCII_SPACE 32
#define DESIRED_PADDING 5
#define MAX_WORD_CHARACTERS 32
#define MAX_WORDS 32

/* @brief Indentifes the type of resource held */
typedef enum resource_type
{
  RESOURCE_TYPE_SHADER = 0,
  RESOURCE_TYPE_TEXTURE,
  RESOURCE_TYPE_MATERIAL,
  RESOURCE_TYPE_VERTEX_BUFFER,
  RESOURCE_TYPE_MESH,
  RESOURCE_TYPE_FONT,
} resource_type;
// -----------------------------------------------------------------------


/**
  @brief Represents an image loaded from stb_lib
*/
typedef struct image
{
  i32 width;      // holds the width of the image
  i32 height;     // holds the height of the image
  i32 channels;   // holds the number of channels used for the image
  u8 *pixels;     // hold the array of pixels for the image

} image;
// -----------------------------------------------------------------------

/**  @brief Represents the texture attachments for a frame buffer  */
typedef enum attachment
{
  ATTACHMENT_POSITION = 0,
  ATTACHMENT_NORMAL,
  ATTACHMENT_COLOR,
  ATTACHMENT_DEPTH,
  ATTACHMENT_TOTAL

} attachment;
// -------------------------------------------------------------------------

/**  @brief Describes data in a uniform, Placed here to expose to all shader types  */
typedef enum uniform_type
{
  UNIFORM_TYPE_INT = 0,
  UNIFORM_TYPE_FLOAT,
  UNIFORM_TYPE_VEC2,
  UNIFORM_TYPE_VEC3,
  UNIFORM_TYPE_VEC4,
  UNIFORM_TYPE_MAT3,
  UNIFORM_TYPE_MAT4

} uniform_type;
// ---------------------------------------------------------------------------

/** @brief Represents a generic shader, implemented in the backend */
typedef struct shader
{
  void* internal_data;  // data maintained by the backend

} shader;
// ----------------------------------------------------------------------------

/** @brief Represents a generic texture */
typedef struct texture
{
  void *internal_data;  // data maintained by the backend

} texture;
// ----------------------------------------------------------------------------

/** @brief Represents a material, texture and lighting, for a mesh */
typedef struct material
{
  texture *albedo;      // color texture to apply
  texture *normal;      // normal map to apply
  u32 albedo_index;     // index to the albedo texture in a texture atlas
  u32 normal_index;     // index to the normal texture in the texture atlas
  f32 reflectivity;     // 0-1 value indicating the reflectivity of teh material

} material;
// ----------------------------------------------------------------------------

/** @brief Represents a 3D point in the engine */
typedef struct vertex
{
  vec3 position;   // 12 bytes
  vec3 noraml;     // 12 bytes
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

} vertex_buffer;
// ----------------------------------------------------------------------------

/** @brief Represents a basic geometry in the engine */
typedef struct mesh
{
  vertex_buffer *buffer;
  material *material;
  b8 is_valid;

} mesh;
// ----------------------------------------------------------------------------

/** @brief Represents a character with texture offsets in a font */
typedef struct glyph
{
  i32 id;           // ascii value of the character
  vec2 tex_coords;  // top left texture coordinates
  vec2 max_coords;  // bottom right texture coordinates
  vec2 size;        // the size of the character in the texture map
  vec2 offset;      // the distance from the left edge of the glyp quad to the cursor
  i32 xadvance;     // how far in pixels the cursor should advance after adding this character

} glyph;
// ----------------------------------------------------------------------------

/* @brief Represents a font with all its glyphs */
typedef struct font
{
  texture *texture_atlas;     // the texture atlas to use
  i32 size;                   // the size of the font
  i32 base;                   // the base offset of the font
  glyph characters[ 256 ];    // array of characters for the font

} font;
// ----------------------------------------------------------------------------

/* @brief represents a group of text */
typedef struct text
{
  char* msg;        // holds the message of the text
  font* fnt;        // font used to render the text
  vec2 cursor;      // the position of the cursor
  f32 font_scale;   // scales the font to the correct size

} text;
// ----------------------------------------------------------------------------
