#include "fzy.h"

void initialize( )
{
  fzy_initialize( "test" );
} // --------------------------------------------------------------------------

void update( )
{
  fzy_tick_begin( );

  // update other systems here

  fzy_tick_end( );
} // --------------------------------------------------------------------------

void shutdown( )
{
  fzy_shutdown( );
} // --------------------------------------------------------------------------

int main()
{
  initialize( );

  while( fzy_is_running() )
  {
    update();
  }

  fzy_shutdown( );
}
