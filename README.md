# FZY Engine
Welcome to the FZY Engine! This README is structured to help document the major systems of the engine and provide space for each component's functions, responsibilities, and implementation notes.

# FZY
  - Provides a fast way to initialize, update and shutdown the engine.  Controls the order of updates so the user doesn't have to, but can
     by not using these functions

  # Functions
  fzy_initialize
      **signature**  b8 fzy_initialize( void )
      **description** Initializes all the subsystems of the engine
      **parameters** None
      **returns**  b8 - true if successfully initializes all subsystems

  fzy_shutdown
      **signature**  void fzy_shutdown( void )
      **description**  Shutdown the engine and frees all resources held by the memory manager
      **parameters**  None
      **returns**  None

  fzy_update
      **signature**  b8 fzy_update( f32 delta )
      **description**  Updates the engine and passes the delta time of the last frame to the subsystems
      **parameters**  
        delta - time since last frame in seconds.
      **returns**  b8 - true if all systems are updated successfully

# Core Systems
  -  Provides fundamental services like memory management, logging, and custom data structures.

# Logger
 - Provides logging functionality for debugging.  Can be removed by changing the LOG_()_ENABLED to 0

  # Functions
  --- FZY FATAL ---
    **signature**  FZY_FATAL( ... )
    **description**  Logs a fatal error in the Engine.  Fatal error stop execution of the engine.
    **parameters**
      ... - formatted string ex FZY_FATAL( "error is %s", error )
    **returns**  None

  --- FZY_ERROR ---
    **signature**   FZY_ERROR( ... )
    **description**  Logs an error in the engine.  Error logs but allow the engine to continue operations.
    **parameters**
      ... - formatted string ex FZY_FATAL( "error is %s", error )
    **returns**  None

  --- FZY_WARNING ---
    **signature**  FZY_WARNING(...)
    **description** Logs a warning in the engine log file.
    **parameters**
      ... - formatted string ex FZY_WARNING( "error is %s", error )
    **returns** None

  --- FZY_INFO ---
    **signature**  FZY_INFO( ... )
    **description**  Logs information in the engine log file.  Good for stepping through functions.
    **parameters**
      ... - formatted string ex FZY_INFO( "error is %s", error )
    **returns** None

  --- FZY_DEBUG ---
    **signature**   FZY_DEBUG( ... )
    **description**  Logs debugging information in the engine log file.
    **parameters**
      ... - formatted string ex FZY_DEBUG( "error is %s", error )
    **returns**  None

# Renderer
  # backend

  # renderer

# Resources

#

Last updated:  [2025-07-08]
