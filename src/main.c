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

#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "macros.h"
#include "structs.h"
#include "init.h"


TheodoraContext theodora;

int main(void)
{
    init(&theodora);

    while(!glfwWindowShouldClose(theodora.window))
    {
        glfwPollEvents();
        nk_glfw3_new_frame(&theodora.glfwctx);

        if(nk_begin(theodora.ctx, "Test", nk_rect(50, 50, 230, 250), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};

            static int op = EASY;
            static int property = 20;
            
            nk_layout_row_static(theodora.ctx, 30, 80, 1);
            if(nk_button_label(theodora.ctx, "button"))
            {
                printf("button preesed\n");
            }

            nk_layout_row_dynamic(theodora.ctx, 30, 2);
            if(nk_option_label(theodora.ctx, "easy", op == EASY))
            {
                op = EASY;
            }
            if(nk_option_label(theodora.ctx, "hard", op == HARD))
            {
                op = HARD;
            }

            nk_layout_row_dynamic(theodora.ctx, 25, 1);
            nk_property_int(theodora.ctx, "Compression: ", 0, &property, 100, 10, 1);
        }
        nk_end(theodora.ctx);

        glClearColor(0x80, 0x00, 0x80, 0xFF);
        glClear(GL_COLOR_BUFFER_BIT);

        nk_glfw3_render(&theodora.glfwctx, NK_ANTI_ALIASING_OFF, THEO_MAX_VERTEX_BUFFER, THEO_MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(theodora.window);
    }

    quit(&theodora);
}

//Changelog:
//23-04-2021 - Added demo code ("borrowed" from Nuklear/demo) to ensure 
//             builds were successful.
//22-04-2021 - Initial version.