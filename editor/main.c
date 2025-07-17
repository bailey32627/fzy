#include "fzy.h"


int main()
{
  fzy_initialize("editor");

  // initialize any systems, components here and register them to the ecs system
  // the order processes are registered is how they will be updated

  // entry for the engine, this is where the engine begins controlling all functionality
  fzy_update();

  // cleans up the engine, freeing all memory used in all systems and processes
  fzy_shutdown( );
}
