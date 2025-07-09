#include "fzy.h"
#include "core/fzy_logger.h"

b8 fzy_initialize( void )
{
  FZY_INFO( "fzy_initialize");
  return true;
} // --------------------------------------------------------------------------

b8 fzy_update( f32 deltaTime )
{
  FZY_INFO( "fzy_update" );
  return true;
} // --------------------------------------------------------------------------

void fzy_shutdown( void )
{
  FZY_INFO( "fzy_shutdown" );
} // --------------------------------------------------------------------------
