#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "helpers.hpp"

#include <iostream>
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace std::string_literals;

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                   SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("Mandelbrot Visualizer", SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    std::string vshader = getCodeFromFile(SOURCE_PATH + "/vshader.glsl"s);
    std::string fshader = getCodeFromFile(SOURCE_PATH + "/fshader.glsl"s);
    unsigned int shader = setUpShaders(vshader.c_str(), fshader.c_str());

    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // bottom left  
         1.0f, -1.0f, 0.0f, // bottom right 
        -1.0f,  1.0f, 0.0f,  // top left

         1.0f, -1.0f, 0.0f, // bottom right  
         1.0f,  1.0f, 0.0f, // top right 
        -1.0f,  1.0f, 0.0f  // top left
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 


    
    SDL_Event e;
    bool running = true;
    while (running)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    SDL_Quit();
    return 0;
}
