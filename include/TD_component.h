//*******************************************************//
//
// File: TD_component.h - Header for all things component related.
// Author: Evan Hess
// Date: 26 April 2021
//
//*******************************************************//

#ifndef TD_COMPONENT_H
#define TD_COMPONENT_H

enum TD_ComponentType
{
    TRANSFORM = 0x0000000000000000, //Everything has a Transform
    RIGIDBODY = 0x0000000000000001,
    SPRITE    = 0x0000000000000002,
    COLLIDER  = 0x0000000000000004,
};

#endif

//Changelog:
//26-04-2021 - Initial version.