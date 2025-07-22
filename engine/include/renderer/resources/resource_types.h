#pragma once

#include "defines.h"
#include "core/fzy_vector.h"


#define ASCII_SPACE 32
#define DESIRED_PADDING 5
#define MAX_WORD_CHARACTERS 32
#define MAX_WORDS 32

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


/** @brief Represents a generic texture */
typedef struct texture
{
  void *internal_data;  // data maintained by the backend

} texture;
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
