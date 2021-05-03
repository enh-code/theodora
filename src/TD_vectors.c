//*******************************************************//
//
// File: TD_vectors.c - Math operations for vectors.
// Author: Evan Hess
// Date: 2 May 2021
//
//*******************************************************//

#include "TD_vectors.h"

TD_Vector2D TD_Vector2D_Add(TD_Vector2D a, TD_Vector2D b)
{
	return (TD_Vector2D){a.x + b.x, a.y + b.y};
}

TD_Vector2D TD_Vector2D_Sub(TD_Vector2D a, TD_Vector2D b)
{
	return (TD_Vector2D){a.x - b.x, a.y - b.y};
}

TD_Vector2D TD_Vector2D_Mult(TD_Vector2D a, float s)
{
	return (TD_Vector2D){a.x * s, a.y * s};
}

TD_Vector2D TD_Vector2D_Div(TD_Vector2D a, float s)
{
	return (TD_Vector2D){a.x / s, a.y / s};
}

float TD_Vector2D_Dot(TD_Vector2D a, TD_Vector2D b)
{
	return a.x * b.x + a.y * b.y;
}

//Changelog:
//02-05-2021 - Initial version.