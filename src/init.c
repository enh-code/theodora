//*******************************************************//
// 
// File: init.c - Initialization source for libraries.
// Author: Evan Hess
// Date: 22 April 2021
// 
//*******************************************************//
#include "init.h"

#include <IL/il.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <stdio.h>

#include "constants.h"

int init(GLFWwindow** window)
{
    //----------DECLARATION----------//

    //GLFW error message
    const char** errorMsg = NULL;
    //General program error
    int error = 0;
    //SDL flags
    Uint32 flags = 0;
    //GLEW error
    GLenum glewError = 0;
    //DevIL error
    ILenum ilError = 0;



    //----------INITIALIZATION----------//
    
    //GLFW (context creation and input handling)
    error = glfwInit();
    if(error == GLFW_FALSE)
    {
        error = glfwGetError(errorMsg);
        fprintf(stderr, "Failed to initialize GLFW. Error: %s\n", *errorMsg);
        return error;
    }

    //Set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    //Create window
    *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Theodora", NULL, NULL);
    if(*window == NULL)
    {
        error = glfwGetError(errorMsg);
        fprintf(stderr, "Window creation failed. Error: %s\n", *errorMsg);
        return error;
    }

    glfwMakeContextCurrent(*window);

    //TODO(Evan): Set callbacks here


    //GLEW (OpenGL loader)
    glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        error = glewError;
        fprintf(stderr, "Failed to initialize GLEW. Error: %s\n", glewGetErrorString(glewError));
        return error;
    }


    //DevIL (image processing)
    ilInit();
    ilClearColor(0xFF, 0xFF, 0xFF, 0x00); //Necessary?
    
    ilError = ilGetError();
    if(ilError != IL_NO_ERROR)
    {
        error = (int)ilError;
        fprintf(stderr, "DevIL failed to initialize. Error: %ud\n", ilError);
        return error;
    }


    //SDL (audio only)
    flags = SDL_INIT_AUDIO;
    
    error = SDL_Init(flags);
    if(error != 0)
    {
        fprintf(stderr, "Failed to initialize SDL. Error: %s\n", SDL_GetError());
        return error;
    }


    //SDL_mixer (increased functionality)
    flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID; //Subject to change (except MP3)
    
    error = Mix_Init((int)flags);
    if(error != (int)flags)
    {
        fprintf(stderr, "Failed to initialize SDL_mixer. Error: %s\n", Mix_GetError());
        return error;
    }

    return 0;
}

void quit(GLFWwindow* window)
{
    //----------CLEANUP----------//
    glfwDestroyWindow(window);

    Mix_Quit();
    SDL_Quit();
    glfwTerminate();
}