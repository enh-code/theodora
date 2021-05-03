//*******************************************************//
//
// File: TD_vectors.h - Vector related structs and functions.
// Author: Evan Hess
// Date: 2 May 2021
//
//*******************************************************//

#ifndef TD_VECTORS_H
#define TD_VECTORS_H

/*
 * TD_Vector2D
 * An abstract for vector operations.
 * 
 * float x: x-component.
 * float y: y-component.
*/
struct TD_Vector2D
{
    float x;
    float y;
};
typedef struct TD_Vector2D TD_Vector2D;

/*
 * TD_Vector2D_Add
 * Adds two vectors together.
 * 
 * TD_Vector2D a: The first vector.
 * TD_Vector2D b: The second vector.
 * 
 * Returns: The resultant vector.
*/
TD_Vector2D TD_Vector2D_Add(TD_Vector2D a, TD_Vector2D b);

/*
 * TD_Vector2D_Sub
 * Subtracts two vectors.
 *
 * TD_Vector2D a: The first vector.
 * TD_Vector2D b: The second vector.
 * 
 * Returns: The resultant vector.
*/
TD_Vector2D TD_Vector2D_Sub(TD_Vector2D a, TD_Vector2D b);

/*
 * TD_Vector2D_Mult
 * Multiplies a vector and a scalar.
 *
 * TD_Vector2D a: The vector.
 * float s: The scalar.
 * 
 * Returns: The resultant vector.
*/
TD_Vector2D TD_Vector2D_Mult(TD_Vector2D a, float s);

/*
 * TD_Vector2D_Div
 * Divides a vector by a scalar.
 *
 * TD_Vector2D a: The vector.
 * float s: The scalar.
 *
 * Returns: The resultant vector.
*/
TD_Vector2D TD_Vector2D_Div(TD_Vector2D a, float s);

/*
 * TD_Vector2D_Sub
 * Calculates the dot product of two vectors.
 *
 * TD_Vector2D a: The first vector.
 * TD_Vector2D b: The second vector.
 *
 * Returns: The dot product.
*/
float TD_Vector2D_Dot(TD_Vector2D a, TD_Vector2D b);

#endif

//Changelog:
//02-05-2021 - Initial version.