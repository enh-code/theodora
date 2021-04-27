//*******************************************************//
//
// File: TD_init.h - Initialization prototypes.
// Author: Evan Hess
// Date: 22 April 2021
//
//*******************************************************//

#ifndef TD_INIT_H
#define TD_INIT_H

#include "TD_structs.h"

/*
 * TD_Init
 *
 * Initializes Theodora with several libraries including:
 *  - GLFW
 *  - GLEW
 *  - DevIL
 *  - Nuklear
 * 
 * TheodoraContext* tc: The context to be initialized.
 * 
 * Returns: 0 for success, non-zero for error 
 *          (details are printed to stderr).
*/
int TD_Init(TheodoraContext* tc);

/*
 * TD_Quit
 *
 * Terminates all libraries and cleans up other various things.
 * 
 * TheodoraContext* tc: The context to be terminated.
 * 
 * Returns: void
*/
void TD_Quit(TheodoraContext* tc);

#endif


//Changelog:
//25-04-2021 - Added TD_ namespace to all functions, changed all filenames,
//             removed SDL requirements.
//23-04-2021 - Added TheodoraContext compatibility, changed the comment format,
//             added this changelog.
//22-04-2021 - Initial version.