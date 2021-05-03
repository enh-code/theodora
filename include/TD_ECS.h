//*******************************************************//
// 
// File: TD_ECS.h - Header for all things entity related.
// Author: Evan Hess
// Date: 26 April 2021
// 
//*******************************************************//

#ifndef TD_ENTITY_H
#define TD_ENTITY_H

#include <stdlib.h>

#include "TD_macros.h"
#include "TD_types.h"
#include "TD_structs.h"
#include "TD_vectors.h"

//----------ENTITY----------//

/*
 * TD_Entity
 * An unique ID for up to 2^64 entities.
*/
typedef TD_uint64 TD_Entity;

/*
 * TD_Signature
 * A bitfield that holds up to 64 components that will be 
 * held by entities.
*/
typedef TD_uint64 TD_Signature;

/*
 * EntityManager
 * Manages entity signatures.
 * 
 * TD_Signature signatures[]: array of entity signatures.
 * char* names[]: holds the names given to the entities in engine.
 * BOOL available[]: holds available indices for signatures.
 * int length: the highest entity index + 1.
 * int active: the number of active entities.
*/
struct TD_EntityManager
{
    TD_Signature signatures[TD_MAX_ENTITIES];
    char* names[TD_MAX_ENTITIES];
    TD_BOOL available[TD_MAX_ENTITIES];
    unsigned int length;
    unsigned int active;
};
typedef struct TD_EntityManager EntityManager;

extern EntityManager entityManager;



//----------COMPONENT----------//

/*
 * TD_ComponentType
 * Various types of components for signatures.
 * 
 * TRANSFORM - Worldspace coordinates and rotation (every entity has one).
 * RIGIDBODY - Physics applications
 * SPRITE    - Rendering 
 * COLLIDER  - Collision detection
*/
enum TD_ComponentType
{
    TRANSFORM = 0x0000000000000000,
    RIGIDBODY = 0x0000000000000001,
    SPRITE    = 0x0000000000000002,
    COLLIDER  = 0x0000000000000004,
    SCRIPT    = 0X0000000000000008
};
typedef enum TD_ComponentType TD_ComponentType;

/*
 * TD_Transform
 * All data relevant to world position and orientation.
 * 
 * TD_Vector2D translate: World-coordinates.
 * TD_Vector2D scale: Size.
 * float angle: Rotation on Z axis.
*/
struct TD_Transform
{
    TD_Vector2D translate;
    TD_Vector2D scale;
    float angle;
};
typedef struct TD_Transform Transform;


/*
 * TD_Rigidbody
 * All data relevant for applied physics.
 * 
 * TD_Vector2D velocity: Speed of entity.
 * TD_Vector2D accleration: Acceleration of entity.
 * TD_Vector2D gravity: Gravity applied to entity.
*/
struct TD_Rigidbody
{
    TD_Vector2D velocity;
    TD_Vector2D acceleration;
    TD_Vector2D gravity;
};
typedef struct TD_Rigidbody Rigidbody;

struct TD_Sprite
{
    char filename[256];
    //Something else?
};
typedef struct TD_Sprite Sprite;

/*
 * TD_Collider
 * All data relevant to collisions.
 * 
 * TD_Vector2D container: The dimensions of the collider.
 * TD_Entity collidedMembers[]: A running list of all members collided in one frame.
 * int collidedCount: The number of actual members.
 * TD_BOOL isCircle: Is it a circle?
 * TD_BOOL isTrigger: Is it only a trigger (no physical restrictions)?
 * TD_BOOL hasCollided: Has it hit something?
*/
struct TD_Collider
{
    TD_Vector2D container;
    TD_Entity collidedMembers[TD_MAX_MEMBERS];
    int collidedCount;
    TD_BOOL isCircle;
    TD_BOOL isTrigger;
    TD_BOOL hasCollided;
};
typedef struct TD_Collider Collider;

/*
 * TD_Script
 * Holds callbacks for gameobjects.
 * 
 * void (*awake)(void): When the gameobject is instantiated 
 *                      for the first time in the game context, 
 *                      this function is run.
 * void (*update)(void): Runs once per frame.
*/
struct TD_Script
{
    void (*awake)(void);
    void (*update)(void);
};
typedef struct TD_Script Script; 

/*
 * TD_ScriptHolder
 * Holds all scripts in use by a gameobject, since more than
 * one script could be used.
 * 
 * Script scripts[5]: The scripts to be used.
*/
struct TD_ScriptHolder
{
    Script scripts[TD_MAX_SCRIPTS];
    int count;
};
typedef struct TD_ScriptHolder ScriptHolder;

/*
 * ComponentManager
 * Manages all component data (it's a lot).
 * 
 * Transform    transforms[]: All transform data.
 * Rigidbody    rigidbodies[]: All rigidbody data.
 * Sprite       sprite[]: All sprite data.
 * Collider     collider[]: All collider data.
 * ScriptHolder scripts[]: All scripts.
*/
struct TD_ComponentManager
{
    Transform    transforms[TD_MAX_ENTITIES];
    Rigidbody    rigidbodies[TD_MAX_ENTITIES];
    Sprite       sprites[TD_MAX_ENTITIES];
    Collider     colliders[TD_MAX_ENTITIES];
    ScriptHolder scripts[TD_MAX_ENTITIES];
};
typedef struct TD_ComponentManager ComponentManager;

extern ComponentManager componentManager;



//----------SYSTEM----------//

void TD_PhysicsSystem(float dt);



//----------FUNCTIONS----------//

/*
 * TD_CreateEntity
 * Creates a new entity in the game.
 * 
 * Transform t: the required transform data.
*/
TD_Entity TD_CreateEntity(Transform t);

/*
 * TD_AddRigidbody
 * Adds a rigidbody to the specified entity.
 * 
 * Rigidbody r: the rigidbody data to be added.
*/
int TD_AddRigidbody(TD_Entity e, Rigidbody r);

/*
 * TD_AddSprite
 * Adds a sprite to the specified entity.
 * 
 * Sprite s: the sprite data to be added.
*/
int TD_AddSprite(TD_Entity e, Sprite s);

/*
 * TD_AddCollider
 * Adds a collider to the specified entity.
 * 
 * Collider c: the collider data to be added.
*/
int TD_AddCollider(TD_Entity e, Collider c);

/*
 * TD_AddScript
 * Adds a script to the specified entity.
 * 
 * Script s: the script data to be added.
*/
int TD_AddScript(TD_Entity e, Script s);

#endif


//Changlog:
//02-05-2021 - Added "TD_uint64" type where applicable, updated 
//             all structs, added TD_PhysicsSystem (WOEFULLY 
//             UNFINISHED).
//28-04-2021 - Collected ECS files into this file, added all of
//             the functionality.
//26-04-2021 - Initial version.