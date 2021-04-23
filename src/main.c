//*******************************************************//
//
// File: main.c - Overall driver program of Theodora.
// Author: Evan Hess
// Date: 22 April 2021
//
//*******************************************************//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <stdio.h>

#include "init.h"

GLFWwindow* window = NULL;

int main(int argc, char** argv)
{
    init(&window);

    quit(window);
}