#include "fzy.h"
#include "core/fzy_hashtable.h"
#include "core/fzy_logger.h"

void test_hashtable( )
{
  hashtable* t = hashtable_create( 64 );

  i32 a[ 10 ] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

  int i = 0;
  hashtable_set( t, "zero", &a[i++] );
  hashtable_set( t, "one", &a[i++] );
  hashtable_set( t, "two", &a[i++] );
  hashtable_set( t, "three", &a[i++] );
  hashtable_set( t, "four", &a[i++] );
  hashtable_set( t, "five", &a[i++] );
  hashtable_set( t, "six", &a[i++] );
  hashtable_set( t, "seven", &a[i++] );
  hashtable_set( t, "eight", &a[i++] );
  hashtable_set( t, "nine", &a[i++] );

  FZY_INFO( "t four = %i", *(i32*)(hashtable_remove( t, "four" ) ) );
  if( hashtable_get( t, "four" ) ) FZY_INFO( "Four still exists" );

  hashtable_destroy( t, NULL );

} // -------------------------------------------------------------------------

int main()
{
  fzy_initialize("editor");

  FZY_INFO( "HELLO" );

  test_hashtable();

  // initialize any systems, components here and register them to the ecs system
  // the order processes are registered is how they will be updated

  // entry for the engine, this is where the engine begins controlling all functionality
  fzy_update();

  // cleans up the engine, freeing all memory used in all systems and processes
  fzy_shutdown( );
}
