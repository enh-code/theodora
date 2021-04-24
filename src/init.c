//*******************************************************//
// 
// File: init.c - Initialization source for libraries.
// Author: Evan Hess
// Date: 22 April 2021
// 
//*******************************************************//
#include "init.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include <stdio.h>

#include "nk.h"

#include "macros.h"


static void set_dark_style(struct nk_context *ctx);

int init(TheodoraContext* tc)
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

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    //Create window
    tc->window = glfwCreateWindow(THEO_WINDOW_WIDTH, THEO_WINDOW_HEIGHT, "Theodora", NULL, NULL);
    if(tc->window == NULL)
    {
        error = glfwGetError(errorMsg);
        fprintf(stderr, "Window creation failed. Error: %s\n", *errorMsg);
        return error;
    }

    glfwMakeContextCurrent(tc->window);

    //TODO(Evan): Set callbacks here


    //GLEW (OpenGL loader)
    glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        error = (int) glewError;
        fprintf(stderr, "Failed to initialize GLEW. Error: %s\n", glewGetErrorString(glewError));
        return error;
    }
    glViewport(0, 0, THEO_WINDOW_WIDTH, THEO_WINDOW_HEIGHT);

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

    //Nuklear
    tc->ctx = nk_glfw3_init(&tc->glfwctx, tc->window, NK_GLFW3_INSTALL_CALLBACKS);
    
    //May not be necessary
    {
        struct nk_font_atlas* atlas;
        nk_glfw3_font_stash_begin(&tc->glfwctx, &atlas);
        nk_glfw3_font_stash_end(&tc->glfwctx);
    }
    
    set_dark_style(tc->ctx);

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

void quit(TheodoraContext* tc)
{
    //----------CLEANUP----------//
    glfwDestroyWindow(tc->window);

    nk_glfw3_shutdown(&tc->glfwctx);

    Mix_Quit();
    SDL_Quit();

    glfwTerminate();
}

static void set_dark_style(struct nk_context *ctx)
{
    struct nk_color table[NK_COLOR_COUNT];
    table[NK_COLOR_TEXT] = nk_rgba(210, 210, 210, 255);
    table[NK_COLOR_WINDOW] = nk_rgba(57, 67, 71, 215);
    table[NK_COLOR_HEADER] = nk_rgba(51, 51, 56, 220);
    table[NK_COLOR_BORDER] = nk_rgba(46, 46, 46, 255);
    table[NK_COLOR_BUTTON] = nk_rgba(48, 83, 111, 255);
    table[NK_COLOR_BUTTON_HOVER] = nk_rgba(58, 93, 121, 255);
    table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(63, 98, 126, 255);
    table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
    table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
    table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
    table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
    table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
    table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
    table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
    table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
    table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
    table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
    table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
    table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
    table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
    table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
    table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
    table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
    nk_style_from_table(ctx, table);
}

//Changelog:
//23-04-2021 - Added set_dark_style (sort of "borrowed" from Nuklear "demo/style.c"),
//             added Nuklear integration.
//22-04-2021 - Initial version.