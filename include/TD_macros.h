//*******************************************************//
//
// File: TD_macros.h - Stores macros for all files.
// Author: Evan Hess
// Date: 22 April 2021 
//
//*******************************************************//

//Simple C boolean
#define TD_BOOL char
#define TD_TRUE 1
#define TD_FALSE 0

//"Borrowed" from Nuklear demos
#define TD_MAX_VERTEX_BUFFER 512 * 1024
#define TD_MAX_ELEMENT_BUFFER 128 * 1024

//Window configuration
#define TD_WINDOW_WIDTH 800
#define TD_WINDOW_HEIGHT 600

//ECS Specifications
#define TD_MAX_ENTITIES 1024
#define TD_MAX_SCRIPTS 5
#define TD_MAX_MEMBERS 10

//Changelog
//02-05-2021 - Added TD_MAX_MEMBERS.
//28-04-2021 - Added TD_ again, added MAX_SCRIPTS.
//26-04-2021 - Added BOOL macro, added MAX_ENTITIES, removed include guards.
//25-04-2021 - Changed "THEO_" to "TD_" for consistency, changed all filenames.
//23-04-2021 - Renamed "constants.h" to "macros.h", swapped constants for
//             #define macros, added "THEO_" prefix.
//22-04-2021 - Initial version.