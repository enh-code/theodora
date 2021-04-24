//*******************************************************//
//
// File: init.h - Initialization prototypes.
// Author: Evan Hess
// Date: 22 April 2021
//
//*******************************************************//
#ifndef INIT_H
#define INIT_H

#include "structs.h"

/*
 * init
 *
 * Initializes Theodora with several libraries including:
 *  - GLFW
 *  - GLEW
 *  - DevIL
 *  - Nuklear
 *  - SDL
 *  - SDL_mixer
 * 
 * TheodoraContext* tc: The context to be initialized.
 * 
 * Returns: 0 for success, non-zero for error 
 *          (details are printed to stderr).
*/
int init(TheodoraContext* tc);

/*
 * quit
 *
 * Terminates all libraries and cleans up other various things.
 * 
 * TheodoraContext* tc: The context to be terminated.
 * 
 * Returns: void
*/
void quit(TheodoraContext* tc);

#endif


//Changelog:
//23-04-2021 - Added TheodoraContext compatibility, changed the comment format,
//             added this changelog.
//22-04-2021 - Initial version.