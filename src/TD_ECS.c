#include "TD_ECS.h"

#include <stdio.h>

EntityManager entityManager;
ComponentManager componentManager;

TD_Entity TD_CreateEntity(Transform t)
{
    TD_Entity e = entityManager.length;

    //Verify that there is space
    if(entityManager.length == MAX_ENTITIES)
    {
        fprintf(stderr, "Maximum number of entities exceeded!\n");
        return MAX_ENTITIES + 1;
    }

    //If there are less being used than are currently available
    if(entityManager.length > entityManager.active)
    {
        //Look for next available 
        for(int i = 0; i < entityManager.length; ++i)
        {
            if(entityManager.available[i] == TD_TRUE)
            {
                entityManager.available[i] = TD_FALSE;
                e = i;
                break;
            }
        }
    }
    else
    {
        ++entityManager.length;
    }

    //Add another entity, reset the signature, and add the data
    ++entityManager.active;
    entityManager.signatures[e] = TRANSFORM;
    componentManager.transforms[e] = t;

    return e;
}

int TD_AddRigidbody(TD_Entity e, Rigidbody r)
{
    //Check if a rigidbody is already present
    if(!(entityManager.signatures[e] & RIGIDBODY))
    {
        fprintf(stderr, "Rigidbody already added!\n");
        return 1;
    }

    //Add the rigidbody and edit signature
    entityManager.signatures[e] |= RIGIDBODY;
    componentManager.rigidbodies[e] = r;

    return 0;
}

int TD_AddSprite(TD_Entity e, Sprite s)
{
    //Check if a sprite is already present
    if(!(entityManager.signatures[e] & SPRITE))
    {
        fprintf(stderr, "Sprite already added!\n");
        return 1;
    }

    //Add the sprite and edit signature
    entityManager.signatures[e] |= SPRITE;
    componentManager.sprites[e] = s;

    return 0;
}

int TD_AddCollider(TD_Entity e, Collider c)
{
    //Check if a collider is already present
    if(!(entityManager.signatures[e] & COLLIDER))
    {
        fprintf(stderr, "Collider already added!\n");
        return 1;
    }

    //Add the collider and edit signature
    entityManager.signatures[e] |= COLLIDER;
    componentManager.colliders[e] = c;

    return 0;
}

int TD_AddScript(TD_Entity e, Script s)
{
    int count = componentManager.scripts[e].count;

    //Check if there is a ScriptHolder
    if(!(entityManager.signatures[e] & SCRIPT))
    {
        entityManager.signatures[e] |= SCRIPT;
    }

    //Verify that there is space
    if(count == MAX_SCRIPTS)
    {
        fprintf(stderr, "Script limit reached!");
        return 1;
    }

    //Add the script
    componentManager.scripts[e].scripts[componentManager.scripts[e].count++] = s;

    return 0;
}


//Changelog:
//28-04-2021 - Initial version.