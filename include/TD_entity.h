//*******************************************************//
// 
// File: TD_entity.h - Header for all things entity related.
// Author: Evan Hess
// Date: 26 April 2021
// 
//*******************************************************//

#ifndef TD_ENTITY_H
#define TD_ENTITY_H

#include <stdlib.h>

/*
 * TD_Entity
 * An unique ID for up to 2^64 entities.
*/
typedef u_int64_t TD_Entity;

/*
 * TD_Signature
 * A bitfield that holds up to 64 components that will be 
 * held by entities.
*/
typedef u_int64_t TD_Signature;

#endif

//Changlog:
//26-04-2021 - Initial version.