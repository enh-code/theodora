//*******************************************************//
// 
// File: nk.h - A helper header for Nuklear.
// Author: Evan Hess
// Date: 23 April 2021
// 
//*******************************************************//
#ifndef NK_NUKLEAR_H_
    #define NK_INCLUDE_FIXED_TYPES
    #define NK_INCLUDE_STANDARD_IO
    #define NK_INCLUDE_STANDARD_VARARGS
    #define NK_INCLUDE_DEFAULT_ALLOCATOR
    #define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
    #define NK_INCLUDE_FONT_BAKING
    #define NK_INCLUDE_DEFAULT_FONT
    #include "nuklear/nuklear.h"
#endif

#ifndef NK_GLFW_GL3_H_
    #define NK_KEYSTATE_BASED_INPUT
    #include "nuklear/nuklear_glfw_gl3.h"
#endif

//Changelog
//23-04-2021 - Initial version.