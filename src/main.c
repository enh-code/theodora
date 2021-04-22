#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "util.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

GLFWwindow* window = NULL;

int main(int argc, char** argv)
{
    const char** errorMsg = NULL;
    int error = 0;
    Uint32 flags = 0;
    GLenum glewError = 1;

    error = glfwInit();
    if(error == GLFW_FALSE)
    {
        error = glfwGetError(errorMsg);
        fprintf(stderr, "Failed to initialize GLFW. Error: %s\n", *errorMsg);
        goto end;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Theodora", NULL, NULL);
    if(window == NULL)
    {
        error = glfwGetError(errorMsg);
        fprintf(stderr, "Window creation failed. Error: %s\n", *errorMsg);
        goto end;
    }

    glfwMakeContextCurrent(window);

    glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        error = glewError;
        fprintf(stderr, "Failed to initialize GLEW. Error: %s\n", glewGetErrorString(glewError));
        goto end;
    }

    flags = SDL_INIT_AUDIO;
    error = SDL_Init(flags);
    if(error != 0)
    {
        fprintf(stderr, "Failed to initialize SDL. Error: %s\n", SDL_GetError());
        goto end;
    }

    flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID;
    error = Mix_Init((int)flags);
    if(error != (int)flags)
    {
        fprintf(stderr, "Failed to initialize SDL_mixer. Error: %s\n", Mix_GetError());
        goto end;
    }
    error = 0;

end:
    glfwDestroyWindow(window);

    Mix_Quit();
    SDL_Quit();
    glfwTerminate();
    return 0;
}