//*******************************************************//
// 
// File: TD_structs.h - Contains various structure definitions.
// Author: Evan Hess
// Date: 23 April 2021
// 
//*******************************************************//

#ifndef TD_STRUCTS_H
#define TD_STRUCTS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TD_nk.h"

/*
 * TD_TheodoraContext
 *
 * Holds general information about the current Theodora context.
 * 
 * struct nk_glfw glfwctx: Something with a Nuklear backend.
 * struct nk_context* ctx: The main context for Nuklear.
 * GLFWwindow* window: The main window for Theodora.
*/
struct TD_TheodoraContext
{
    struct nk_glfw glfwctx;
    struct nk_context* ctx;

    GLFWwindow* window;
};
//For convenience: 
typedef struct TD_TheodoraContext TD_TheodoraContext;
typedef struct TD_TheodoraContext TheodoraContext;

#endif


//Changelog
//25-04-2021 - Changed all filenames.
//23-04-2021 - Initial version.