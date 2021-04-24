//*******************************************************//
// 
// File: structs.h - Contains various structure definitions.
// Author: Evan Hess
// Date: 23 April 2021
// 
//*******************************************************//
#ifndef STRUCTS_H
#define STRUCTS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nk.h"

/*
 * TheodoraContext
 *
 * Holds general information about the current
 *     Theodora context.
 * 
 * struct nk_glfw glfwctx: Something with a Nuklear 
 *     backend.
 * struct nk_context* ctx: The main context for 
 *     Nuklear.
 * GLFWwindow* window: The main window for Theodora.
 * 
*/
struct TheodoraContext
{
    struct nk_glfw glfwctx;
    struct nk_context* ctx;

    GLFWwindow* window;
};

typedef struct TheodoraContext TheodoraContext;

#endif

//Changelog
//23-04-2021 - Initial version.