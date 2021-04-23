//*******************************************************//
//
// File: init.h - Initialization prototypes.
// Author: Evan Hess
// Date: 22 April 2021
//
//*******************************************************//
#ifndef INIT_H
#define INIT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * Function: init
 * --------------
 * Initializes Theodora with several libraries including:
 *  - GLFW
 *  - GLEW
 *  - DevIL
 *  - SDL
 *  - SDL_mixer
 * 
 * GLFWwindow** window: The window to be initialized.
 * 
 * Returns: 0 for success, non-zero for error 
 *          (details are printed to stderr).
*/
int init(GLFWwindow** window);

/*
 * Function: quit
 * --------------
 * Terminates all libraries and cleans up other various things.
 * 
 * GLFWwindow* window: The window to be destroyed.
 * 
 * Returns: void
*/
void quit(GLFWwindow* window);

#endif