#include "TD_ECS.h"

#include <stdio.h>
#include <math.h>

EntityManager entityManager;
ComponentManager componentManager;

TD_Entity TD_CreateEntity(Transform t)
{
    TD_Entity e = entityManager.length;

    //Verify that there is space
    if(entityManager.length == TD_MAX_ENTITIES)
    {
        fprintf(stderr, "Maximum number of entities exceeded!\n");
        return TD_MAX_ENTITIES + 1;
    }

    //If there are less being used than are currently available
    if(entityManager.length > entityManager.active)
    {
        //Look for next available 
        for(TD_Entity i = 1; i < entityManager.length; ++i)
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
    if(count == TD_MAX_SCRIPTS)
    {
        fprintf(stderr, "Script limit reached!");
        return 1;
    }

    //Add the script
    componentManager.scripts[e].scripts[componentManager.scripts[e].count++] = s;

    return 0;
}



//----------SYSTEMS----------//

TD_BOOL TD_HasIntersection(TD_Entity i, TD_Entity j)
{
    TD_Vector2D ac = componentManager.colliders[i].container;
    TD_Vector2D bc = componentManager.colliders[j].container;

    TD_Vector2D at = componentManager.transforms[i].translate;
    TD_Vector2D bt = componentManager.transforms[j].translate;

    //Check if they are both circles
    if(componentManager.colliders[i].isCircle && componentManager.colliders[j].isCircle)
    {
        float r = ac.x / 2 + bc.x / 2;
        float h = (bt.x + bc.x / 2) - (at.x + ac.x / 2);
        float k = (bt.y + bc.x / 2) - (at.y + ac.x / 2);

        //Distance between midpoints is sqrt((h2 - h1)^2 + (k2 - k1)^2), no sqrt is used for optimization
        float dist = h * h + k * k;

        return (dist <= r * r) ? TD_TRUE : TD_FALSE;
    }


    //Assume two rectangles
    if(at.x + ac.x < bt.x || bt.x + bc.x < at.x)
    {
        return TD_FALSE;
    }

    if(at.y + ac.y < bt.y || bt.y + bc.y < at.y)
    {
        return TD_FALSE;
    }

    return TD_TRUE;
}

void TD_PhysicsSystem(float dt)
{
    TD_Vector2D acceleration;
    TD_BOOL hasCollided;;

    //TODO(Evan): Reset frame specific variables.

    for(TD_Entity i = 1; i < entityManager.length; ++i)
    {
        //Must have a collider
        if((entityManager.signatures[i] & COLLIDER) == COLLIDER)
        {
            //Bad time complexity, I know, this is temporary (hopefully)
            for(TD_Entity j = i + 1; j < entityManager.length - 1; ++j)
            {
                if((entityManager.signatures[i] & COLLIDER) == 0)
                {
                    continue;
                }

                //Check for collision
                if(TD_HasIntersection(i, j))
                {
                    if(!componentManager.colliders[i].hasCollided)
                    {
                        componentManager.colliders[i].hasCollided = TD_TRUE;
                    }

                    if(componentManager.colliders[i].collidedCount < TD_MAX_MEMBERS)
                    {
                        componentManager.colliders[i].collidedMembers[componentManager.colliders[i].collidedCount++] = j;
                    }

                    if(!componentManager.colliders[j].hasCollided)
                    {
                        componentManager.colliders[j].hasCollided = TD_TRUE;
                    }

                    if(componentManager.colliders[j].collidedCount < TD_MAX_MEMBERS)
                    {
                        componentManager.colliders[j].collidedMembers[componentManager.colliders[j].collidedCount++] = i;
                    }
                }
            }
        }

        //TODO(Evan): Account for cases where the object continues to move.

        //Has collided and not a trigger or missing rigidbody component?
        if((componentManager.colliders[i].hasCollided && !componentManager.colliders[i].isTrigger) || (entityManager.signatures[i] & RIGIDBODY) == 0)
        {
            continue;
        }

        acceleration = TD_Vector2D_Add(componentManager.rigidbodies[i].acceleration, componentManager.rigidbodies[i].gravity);

        //Basic kinematic equations (x = x0 + v0 * t + .5 * a * t^2)
        //x-component
        componentManager.transforms[i].translate.x +=
            componentManager.rigidbodies[i].velocity.x * dt + 0.5f * acceleration.x * dt * dt;
        //y-component
        componentManager.transforms[i].translate.y +=
            componentManager.rigidbodies[i].velocity.y * dt + 0.5f * acceleration.y * dt * dt;
    }
}


//Changelog:
//02-05-2021 - Added TD_PhysicsSystem (it's really messed 
//             up right now), renamed macros.
//28-04-2021 - Initial version.