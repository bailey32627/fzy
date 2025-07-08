# FZY Engine
Welcome to the FZY Engine — a modular, lightweight game engine built for flexibility and performance. This README serves as an overview and technical reference for each major subsystem in the engine.

## Table of Contents
- [Logger](#logger)
- 

## FZY
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

## Logger
 - Provides logging functionality for debugging.  Can be removed by changing the LOG_()_ENABLED to 0

## `FZY_FATAL( ... )`  
Logs a fatal error in the Engine.  Fatal error stop execution of the engine.  

**Parameters:**
- `...` - formatted string ex FZY_FATAL( "error is %s", error )

**Returns:**
None

## `FZY_ERROR( ... )`  
Logs an error in the engine.  Error logs but allow the engine to continue operations.  

**Parameters:**
- `...` - formatted string ex FZY_ERROR( "error is %s", error )

**Returns:**  
None

## `FZY_WARNING(...)`  
Logs a warning in the engine log file.  

**Parameters:**  
- `...` - formatted string ex FZY_WARNING( "error is %s", error )

**Returns:**  
None

## `FZY_INFO( ... )`
Logs information in the engine log file.  Good for stepping through functions.  

**Parameters:**
- `...` - formatted string ex FZY_INFO( "error is %s", error )  

**Returns:**  
None

## `FZY_DEBUG( ... )`
Logs debugging information in the engine log file.  

**Parameters:**  
- `...` - formatted string ex FZY_DEBUG( "error is %s", error )  

**Returns:**  
None

# Mathematics
define some commonly used mathematical terms and functions

## `FZY_PI`
An approximate representation of PI

## `ONE_OVER_PI`
One divided by an approximate representation of PI

## `degrees_to_radian( angle )`
Converts degrees to radians  

**Parameters:**  
- `angle` - The angle in degrees to convert to radian  

**Returns:**  
f32

## `fzy_radian_to_degrees( radians )`
convers radians to degrees

**Parameters**  
- `radians` - Radians to convert to degrees  

**Returns:**
f32

## `fzy_clamp( v, bottom, top )`
Clamps the value between bottom and top  

**Parameters:**  
- v - the value to clamp
- bottom - the lowest value the number can be
- top - the highest value the number can be  

**Returns:**
f32

## `fzy_between( v, bottom, top )`  
Checks if the value is between top and bottom  

**Parameters:**  
- v - The value to test
- bottom - the lowest value to check if v is equal to or larger than
- top - the highest value to check if v is equal to or less than  

**Returns:**  
`true` if v is between bottom and top

## `fzy_lerp( a, b, ratio )`
Linear interpolates a and b by ratio  

**Parameters:**  
- a - the start value to interpolate
- b - the end value to interpolate
- ratio - the ratio to interpolate between a and b  

**Returns:**  
f32 - value of a interpolated to b by ratio

## `fzy_smooth_step( a, b, ratio )`
A smoother interpolation of a and b by ratio  

**Parameters:**  
- a - the start value to interpolate
- b - the end value to interpolate
- ratio - the ratio to interpolate between a and b  

**Returns:**  
f32 - value of a interpolated to b by ratio

## `fzy_smoother_step( a, b, ratio )`
Even smoother interpolation of a and b by ratio  

**Parameters:**  
- a - the start value to interpolate
- b - the end value to interpolate
- ratio - the ratio to interpolate between a and b  

**Returns:**  
f32 - value of a interpolated to b by ratio

## `fzy_min( a, b )`
Returns the minimum number of a and b  

**Parameters:**  
- a - the first value to check
- b - the second value to check  

**Returns:**
f32 - returns the lowest value a or b  

## `fzy_max( a, b )`
Returns the max number of a and b  

**Parameters:**  
- a - the first value to check
- b - the second value to check  

**Returns:**
f32 - returns the highest value a or b  

## `seconds_to_ms( seconds )`  
Converts seconds to milliseconds

**Parameters:**  
- seconds - the amount of seconds to convert to ms  

**Returns:**
f32 - seconds converted to milliseconds

## `ms_to_seconds( ms )`
Converts ms to seconds  

**Parameters:**  
- ms - the amount of ms to convert to seconds  

**Returns:**
f32 - ms converted to seconds  

## `FZY_INFINITY`  
A huge number that should be larger tan any valid number used

## `FZY_EPSILON`
Smallest positive number where 1.0 + FLOAT_EPSILON != 0

## `f32 fzy_sin( f32 v )`
Calculates the sine of v

**Parameters:**  
- v - the number to calculate the sine of  

**Returns:**
f32 - the sine of v

## `f32 fzy_cos( f32 v )`
Calculates the cosine of v  

**Parameters:**  
- v - the number to calculate the cosine of  

**Returns:**  
f32 - the cosine of v  

## `f32 fzy_tan( f32 v )`
Calculate the tangent of v  

**Parameters:**  
- v - the number to calculate the tangent of  

**Returns:**  
f32 - the tangent of v  

## `f32 fzy_acos( f32 v )`
Calculates the arc cosine of v  

**Parameters:**  
- v - the number to calculate the arc cosine of  

**Returns:**
f32 - the arc cosine of v

## `f32 fzy_sqrt( f32 v )`
Calculates the square root of v  

**Parameters:**  
- v - the number to calculate the square root of  

**Returns:**  
f32 - the square root of v  

## `f32 fzy_abs( f32 v )`
Calculate the absolute value of v  

**Parameters:**  
- v - the number to get the absolute value of  

**Returns:**  
f32 - the absolute value of x

## `b8 fzy_is_power_of_2( u64 v )`
Indicates if the value is a power of 2  

**Parameters:**  
- v - the value to be interpreted

**Returns:**  
`true` if is a power of 2

## `i32 random()`
Generates a random integer

**Parameters:**  
- None  

**Returns:**  
i32 - A random integer  

## `i32 random_in_range( i32 min, i32 max )`
Generates a random integer that is within the range min and max  

**Parameters:**  
- min - minimum number in the range
- max - maximum number in the range  

**Returns:**
i32 - A random integer

## `f32 random_f32()`
Generates a random float  

**Parameters:**  
- None  

**Returns:**  
f32 - A random f32  

## `f32 random_in_range_f32( f32 min, f32 max )`
Generates a random f32 that is within the range min and max  

**Parameters:**  
- min - minimum number in the range
- max - maximum number in the range

**Returns:**  
f32 - A random integer

## i32 `fzy_floor( f32 v )`
Rounds down the given value  

**Parameters:**  
- v - the number to round down

**Returns:**  
i32 - the number rounded down  

# ivec2

## `ivec2 ivec2_create( i32 x, i32 y )`
Creates and returns a new ivec2  

**Parameters:**  
- x - the value for first element
- y - the value for the second element  

**Returns:**  
ivec2 - new 2-element vector

## `ivec2 ivec2_add( ivec2 a, ivec2 b )`  
Adds the two 2D vectors and returns the result  

**Parameters:**  
- a - the first vector  
- b - the second vector  

**Returns:**  
ivec2 - new 2 integer vector

## `ivec2 ivec2_subtract( ivec2 a, ivec2 b )`
Subtracts the two vectors and returns the result  

**Parameters:**  
- a - the first vector  
- b - the second vector  

**Returns:**  
ivec2 - new 2 element vector

## `ivec2 ivec2_multiply( ivec2 a, ivec2 b )`
Multiples the two vectors and returns the result  

**Parameters:**
- a - the first vector
- b - the second vector  

**Returns:**  
ivec2 - new 2 element vector

# vec2

## `vec2 vec2_create( f32 x, f32 y )`
Creates and returns a new 2 element vector  

**Parameters:**  
- x - the x value of the vector
- y - the y value of the vector  

**Returns:**  
vec2 - new 2 element vector with x and y values

## `vec2 vec2_up()`
Creates a 2 element vector pointing up (0, 1 )  

**Parameters:**  
- None  

**Returns:**  
vec2 - vec2 set to (0,1)

## `vec2 vec2_down()`  
Creates a 2 element vector pointing down (0, -1 )  

**Parameters:**  
- None  

**Returns:**  
vec2

## `vec2 vec2_left()`
Creates a 2 element vector pointing left ( -1, 0 )  

**Parameters:**  
- None  

**Returns:**  
vec2

## `vec2 vec2_right()`
Creates a 2 element vector pointing right ( 1, 0 )  

**Parameters:**  
- None  

**Returns:**  
vec2

## `vec2 vec2_add( vec2 a, vec2 b )`
Adds the two vectors and returns the result
**Parameters:**  
- a - the first vector  
- b - the second vector  

**Returns:**  
vec2 - new 2 element vector that is the sum of a and b

## `vec2 vec2_subtract( vec2 a, vec2 b )`
Subtracts the two vectors and return the difference  

**Parameters:**
- a - the first vector
- b - the second vector   

**Returns:**
vec2 - new 2 element vector that is the difference of a and b  

## `vec2 vec2_multiply( vec2 a, vec2 b )`
Multiplies the two vectors and return the product  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
vec2 - new 2 element vector that is the product of a and b

## `vec2 vec2_divide( vec2 a, vec2 b )`
Divides the two supplied vectors and returns the quotient  

**Parameters:**  
- a - the numerator
- b - the denominator  

**Returns:**   
vec2 - new 2 element vector that is the quotient of a and b

## `vec2 vec2_scale( vec2 v, f32 s )`  
Scales the supplied vector by the scalar and returns the result  

**Parameters:**  
- v - the vector to scale
- s - the scalar value  

**Returns:**  
vec2 - new 2 element vector that is v scaled by s

## `vec2 vec2_rotate( vec2 v, f32 degrees )`
Rotates the given vector by the angle  

**Parameters:**  
- v - the vector to rotate
- degrees - the angle to rotate by in degrees  

**Returns:**  
vec2 - new vec2 that is v rotated by degrees

## `f32 vec2_length_squared( vec2 v )`
Calculates the squared length of the provided vector  

**Parameters:**  
- v - the vec2 to get the squared length of  

**Returns:**  
f32 - the squared length of v

## `f32 vec2_dot( vec2 a, vec2 b )`
Calculates the dot product of the provided vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32 - the dot product of the vectors

## `f32 vec2_length( vec2 v )`
Calculates the length of the provided vector  

**Parameters:**  
- v - the vector  

**Returns:**
f32 - the length of the vector  

## `vec2 vec2_normalize( vec2 v )`
Calculates a normalized copy of the supplied vector  

**Parameters:**  
- v - the vector to be normalized  

**Returns:**  
vec2 - a normalized version of v

/*
    @brief
    @param
    @return true if within tolerance
*/
FZY_INLINE b8 vec2_compare( vec2 a, vec2 b, f32 tolerance )
Compares all elements of a and b and ensure the difference is less than the tolerance  

**Parameters:**  
- a - the first vector
- b - the second vector
- tolerance - the difference tolerance, typically FZY_EPSILON or similar  

**Returns:**  
b8 - true if within tolerance

## `f32 vec2_distance_squared( vec2 a, vec2 b )`
Calculates the squared distance between the two vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32 - the squared distance between a and b

## `f32 vec2_distance( vec2 a, vec2 b )`
Calculates the distance between a and b  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32 - the distance between a and b

# vec3

## `vec3 vec3_create( f32 x, f32 y, f32 z )`  
Creates a new 3 element vector with the given values  

**Parameters:**  
- x - the x value
- y - the y value
- z = the z value  

**Returns:**  
vec3

## `vec3 vec3_zero( void )`
Creates a vec3 with elements set to zero  

**Parameters:**  
- None  

**Returns:**  
vec3

## `vec3 vec3_up( void )`
Creates a vec3 that represents the up direction  

**Parameters:**  
-None  

**Returns:**  
vec3

## vec3 `vec3_down( void )`
Creates a vec3 that represents the down direction  

**Parameters:**  
- None
**Returns:**  
vec3

## `vec3 vec3_forward( void )`  
 Creates a vec3 that represents the forward direction  

**Parameters:**  
- None  

**Returns:**  
vec3

## `vec3 vec3_backward( void )`
Creates a vec3 that represents the backward direction  

**Parameters:**  
- None  

**Returns:**  
vec3

## `vec3 vec3_add( vec3 a, vec3 b )`  
Calculates the sum of the two vectors  

**Parameters:**  
@param a - the first vector
@param b - the second vector  

**Returns:**  
vec3 - new vec3 that is the sum of the elements of a and b

## `vec3 vec3_subtract( vec3 a, vec3 b )`
Calculates the difference of the two vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
vec3 - new vec3 that is the difference of the elements of a and b

## `vec3 vec3_multiply( vec3 a, vec3 b )`
Calculate the product of vectors a and b  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
vec3 - the product of a and b

## `vec3 vec3_scale( vec3 v, f32 s )`  
Calculates a vector that is the product of scaling the given vector  

**Parameters:**  
- v - the vector to scale
- s - the scalar to use  

**Returns:**  
vec3 - the product of scaling v by s

## `vec3 vec3_invert( vec3 v )`
Returns a mirror image of the provided vector  

**Parameters:**  
- v - the vector to invert  

**Returns:**
vec3

## `vec3 vec3_cross( vec3 a, vec3 b )`
Calculates the cross product of the supplied vectors. The cross product is a vector which is ortoganal to both provided vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
vec3 - Orthonanal vector to both a and b

## f32 vec3_dot( vec3 a, vec3 b )
Calculates the dot product of the two supplied vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32

## `vec3_length_squared( vec3 v )`  
Calculates the squared length of the vector  

**Parameters:**  
- v - the vector to calculate the length of  

**Returns:**  
f32

## `f32 vec3_length( vec3 v )`
Calculates the length ( magnitude ) of the vector  

**Parameters:**  
- v - the vector to find the length of  

**Returns:**  
f32

## `f32 vec3_distance_squared( vec3 a, vec3 b )`
Calculates the squared distance between 2 vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32

## `f32 vec3_distance( vec3 a, vec3 b )`  
Calculates the distance between the 2 vectors  

**Parameters:**  
- a - the first vector
- b - the second vector  

**Returns:**  
f32  

## `vec3 vec3_normalize( vec3 v )`  
Calculates a normalized version of the provided vector  

**Parameters:**  
- v - the vector to normalize  

**Returns:**  
vec3 - normalized copy of v

## `vec3 vec3_reflect( vec3 a, vec3 normal )`  
Calculates a vector that is reflected across the provided normal  

**Parameters:**  
- a - the vector to reflect
- normal - the normal vector to reflect across  

**Returns:**  
vec3

## `vec3 vec3_project( vec3 a, vec3 b )`  
Calculates a vector projected onto b  

**Parameters:**  
- a - the vector to project
- b - the vector to project onto  

**Returns:**  
vec3  

## `b8 vec3_compare( vec3 a, vec3 b, f32 tolerance )`
Compares all elements of a and b and ensures the difference is less than tolerance  

**Parameters:**  
- a - the first vector
- b - the second vector
- tolerance - the difference tolerance.  Typically FZY_EPSILON or similar  

**Returns:**  
b8 - true if within tolerance

## `vec3 vec3_transform( vec3 v, mat4 m )`
Transform a point by a 4x4 matrix.  NOTE: It is assumed by this function that the vector v is a point, not a direction, and is calculated as if a w component with a value of 1.0f is there  

**Parameters:**  
- v - the point vector
- m - the transform matrix  

**Returns:**  
vec3 - v transformed by m  

## `vec3 vec3_transform_mat3( vec3 v, mat3 m )`
Transforms a vector by 3x3 matrix.  

**Parameters:**  
- v - the vector to transform
- m - the matrix to transform by  

**Returns:**  
vec3

# vec4

## `vec4 vec4_create( f32 x, f32 y, f32 z, f32 w )`
Creates a 4 element vector with the given values  

**Parameters:**  
- x - the x value of the vector
- y - the y value of the vector
- z - the z value of the vector
- w - the w value of the vector  

**Returns:**  
vec4

## `vec4 vec4_identity()`
Creates an identity quaternion  

**Parameters:**  
- None  

**Returns:**  
vec4

## `f32 vec4_length( vec4 v )`  
Calculates the length of the provided vector  

**Parameters:**  
- a - the vector to retrieve the length of  

**Returns:**
f32

## `vec4 vec4_normalize( vec4 q )`
Calculates a normalized copy of the provided quaternion
**Parameters:**  
-q - the quaternion to normalize  

**Returns:**  
vec4

## `vec4 vec4_conjugate( vec4 q )`
Calculates the conjugate of the provided quaternion.  That is, the x,y,z elements are negated, but the w element is untouched.  

**Parameters:**  
- q - the quaternion to obtain the conjugate of  

**Returns:**  
vec4

## `vec4 vec4_inverse( vec4 q )`
Calculates an inverse copy of the provided quaternion  

**Parameters:**  
- q - the quaternion to invert  

**Returns:**  
vec4

## `vec4 vec4_multiply( vec4 a, vec4 b )`
Multiplies the provided quaternions.  Not communicable, ie a * b is not = to b * a  

**Parameters:**  
- a - the first quaternion
- b - the second quaternion  

**Returns:**  
vec4  

## `f32 vec4_dot( vec4 a, vec4 b )`
Calculates the dot product of the provided quaternions  

**Parameters:**  
- a - the first quaternion
- b - the second quaternion  

**Returns:**  
f32

## `vec4 vec4_from_axis_angle( vec3 axis, f32 angle, b8 normalize )`
Calculates a rotation quaternion from the given axis and angle  

**Parameters:**  
- axis - the axis of the rotation
- angle - the angle of the rotation in degrees  
- normalize - indicates if the quaternion should be normalized  

**Returns:**
vec4

## `vec4 vec4_slerp( vec4 a, vec4 b, f32 percentage )`
Calculates spherical linear interpolation of a given percentage between two quaternions  

**Parameters:**  
- a - the first quaternion
- b - the second quaternion
- percentage - the percentage of interpolation, typically a value from 0.0f to 1.0f  

**Returns:**
vec4 - a quaternion representing a interpolated with b by percentage

## `b8 vec4_compare( vec4 a, vec4 b, f32 tolerance )`  
Compares all elements of a and b and ensures the difference is less than tolerance  

**Parameters:**  
- a - the first vector
- b - the second vector
- tolerance - the difference tolerance.  Typically FZY_EPSILON  

**Returns:**  
b8 - true if within tolerance

# mat3

## `mat3 mat3_create( f32 xx, f32 xy, f32 xz, f32 yx, f32 yy, f32 yz, f32 zx, f32 zy, f32 zz )`
Creates a new 3x3 matrix  

**Parameters:**  
- xx - zz - the individual values of each of the elements  

**Returns:**  
mat3 - a new matrix with elements set to the given values  

## `mat3 mat3_identity( void )`
Creates a matrix that is set to the identity matrix  

**Parameters:**  
- None  

**Returns:**
mat3

## `mat3 mat3_zero( void )`
Creates a matrix with all elements set to zero  

**Parameters:**  
- None  

**Returns:**  
mat3  

## `mat3 mat3_multiply( mat3 a, mat3 b )`
Multiplies the matrices and returns the result  

**Parameters:**  
- a - the first matrix
- b - the second matrix  

**Returns:**  
mat3  

## `mat3 mat3_transpose( mat3 m )`  
Returns a transposed version of the provided matrix  

**Parameters:**  
- m - the matrix to transpose  

**Returns:**  
mat3

## `mat3 mat3_skew_symmetric( vec3 v )`
Calculates a skew symmetric matrix for inertia tensors  

**Parameters:**  
- v - the vector to set a skew sysmmetric for  

**Returns:**  
mat3

## `mat3 mat3_inverse( mat3 m )`
Creates an inverse of the provided matrix  

**Parameters:**  
- m - the matrix to calculate the inverse of  

**Returns:**
mat3

# mat4

## `mat4 mat4_identity( void )`
Creates an identity matrix  

**Parameters:**  
- none  

**Returns:**  
mat4  

## `mat4 mat4_zero( void )`  
Creates a matrix with all elements set to zero  

**Parameters:**  
- none  

**Returns:**  
mat4

## `mat4 mat4_multiply( mat4 a, mat4 b )`
Calculates the product of the two matrices  

**Parameters:**  
- a - The first matrix
- b - the second matrix  

**Returns:**  
mat4

/*
  @brief
  @param
  @return mat4 - A new orthographic projection matrix.
*/
FZY_INLINE mat4 mat4_orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
Creates and returns an orthographic projection matrix. Typically used to render flat or 2D scenes.  

**Parameters:**  
- left - The left side of the view frustum.
- right - The right side of the view frustum.
- bottom - The bottom side of the view frustum.
- top - The top side of the view frustum.
- near_clip - The near clipping plane distance.
- far_clip - The far clipping plane distance.  

**Returns:**  
mat4

## `mat4 mat4_perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)`
Creates and returns a perspective matrix. Typically used to render 3d scenes.  

**Parameters:**  
- fov_radians - The field of view in radians.
- aspect_ratio - The aspect ratio.
- near_clip - The near clipping plane distance.
- far_clip - The far clipping plane distance.  

**Returns:**  
mat4

## `mat4 mat4_look_at(vec3 position, vec3 target, vec3 up)`
Creates and returns a look-at matrix, or a matrix looking at target from the perspective of position.  

**Parameters:**  
- position - The position of the matrix.
- target - The position to "look at".
- up - The up vector.  

**Returns:**  
mat4

## `mat4 mat4_transpose( mat4 a )`
Returns a transposed copy of the provided matrix (rows->columns)  

**Parameters:**  
- matrix - the matrix to transpose  

**Returns:**
mat4

## `mat4 mat4_inverse( mat4 matrix )`
Creates and returns an inverse of the provided matrix.  

**Parameters:**  
- matrix - the matrix to invert  

**Returns:**  
mat4

## `mat4 mat4_translation(vec3 position )`
Creates and returns a translation matrix from the given position.  

**Parameters:**  
- position - The position to be used to create the matrix.  

**Returns:**  
mat4

## `vec3 mat4_rotate_vec3( mat4 *matrix, vec3 vec )`
Rotates the given vec3 by the matrix rotation, no translation  

**Parameters:**  
- matrix - The matrix to get rotation from
- vec - The vec3 to rotate  

**Returns:**  
vec3

## `mat4 mat4_scale( vec3 scale )`
Returns a scale matrix using the provided scale.  

**Parameters:**
- scale - 3 component scalar  

**Returns:**
mat4


## `vec3 mat4_forward( mat4 a )`
Returns a forward vector relative to the provided matrix.  

**Parameters:**  
- a - The matrix from which to base the vector.  

**Returns:**  
vec3

## `vec3 mat4_backward( mat4 a )`
Returns a backward vector relative to the provided matrix.  

**Parameters:**  
- a - the matrix from which to base the vector  

**Returns:**  
vec3 - directional vector

## `vec3 mat4_up( mat4 a )`  
Returns a upward vector relative to the provided matrix.  

**Parameters:**  
- a - the matrix from which to base the vector  

**Returns:**  
vec3 - a 3 component directional vector

## `vec3 mat4_down( mat4 a )`
Returns a downward vector relative to the provided matrix.  

**Parameters:**  
- a - the matrix from which to base the vector  

**Returns:**  
vec3

## `vec3 mat4_left( mat4 a )`  
Returns a left vector relative to the provided matrix.  

**Parameters:**  
- a - The matrix from which to base the vector.  

**Returns:**
vec3

## `vec3 mat4_right(mat4 a )`  
Returns a right vector relative to the provided matrix.  

**Parameters:**  
- a - The matrix from which to base the vector.  

**Returns:**  
vec3

## `mat4 mat4_create_transform( vec3 position, vec3 scale, vec3 rotation )`  
Returns a transformation matrix created from the position scale and rotation  

**Parameters:**  
- position - Position to use
- scale - Scale to use
- rotation - Rotation to use  

**Returns:**
mat4

## `mat4 vec4_to_mat4( vec4 q )`
Creates a rotation matrix from the given quaternion.  

**Parameters:**  
- q - The quaternion to be used.  

**Returns:**
mat4

## `mat4 vec4_to_rotation_matrix(vec4 q, vec3 center )`
Calculates a rotation matrix based on the quaternion and the passed in center point.  

**Parameters:**  
- q - The quaternion.
- center - The center point.  

**Returns:**
mat4

## `vec3 mat4_transform_vec3( mat4 m, vec3 v )`
Transforms a vec3 by the given mat4  

**Parameters:**  
- m - the matrix to transform by
- v - the vector to transform  

**Returns:**  
vec3

## `vec3 mat4_transform_transpose_vec3( mat4 m, vec3 v )`
Transforms the vec3 by the transpose of the given matrix  

**Parameters:**  
- m - matrix to transform by
- v - the vector to transform  

**Returns:**  
vec3


Last updated:  [2025-07-08]
