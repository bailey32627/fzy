# FZY Engine
Welcome to the FZY Engine! This README is structured to help document the major systems of the engine and provide space for each component's functions, responsibilities, and implementation notes.

# FZY
Provides a fast way to initialize, update and shutdown the engine.  Controls the order of updates so the user doesn't have to, but can by not using these functions

## `b8 fzy_initialize( void )`
Initializes all the subsystems of the engine 

**Parameters:**  
- None

**Returns:**  
   `true` if all subsystems initialize correctly
   
## `void fzy_shutdown( void )`
Shutdown the engine and frees all resources held by the memory manager  

**parameters:**  
- None  

**Returns:**  
None

## `b8 fzy_update( f32 delta )`
Updates the engine and passes the delta time of the last frame to the subsystems

**Parameters:**   
- delta - time since last frame in seconds.
  
**Returns:**  
`true` if all systems are updated successfully

# Logger
 - Provides logging functionality for debugging.  Can be removed by changing the LOG_()_ENABLED to 0

## `FZY_FATAL( ... )`  
Logs a fatal error in the Engine.  Fatal error stop execution of the engine.  

**Parameters:**
- ... - formatted string ex FZY_FATAL( "error is %s", error )

**Returns:**
None

## `FZY_ERROR( ... )`  
Logs an error in the engine.  Error logs but allow the engine to continue operations.  

**Parameters:**
- ... - formatted string ex FZY_ERROR( "error is %s", error )
   
**Returns:**  
None

## `FZY_WARNING(...)`  
Logs a warning in the engine log file.  

**Parameters:**  
- ... - formatted string ex FZY_WARNING( "error is %s", error )

**Returns:**  
None

## `FZY_INFO( ... )`
Logs information in the engine log file.  Good for stepping through functions.  

**Parameters:**
- ... - formatted string ex FZY_INFO( "error is %s", error )  
  
**Returns:**  
None

## `FZY_DEBUG( ... )`
Logs debugging information in the engine log file.  

**Parameters:**  
- ... - formatted string ex FZY_DEBUG( "error is %s", error )  

**Returns:**  
None


Last updated:  [2025-07-08]
