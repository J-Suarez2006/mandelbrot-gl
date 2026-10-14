#ifndef FRACTALGL_HPP
#define FRACTALGL_HPP

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Camera
{
    private:
    float m_aspect_ratio;
    float m_height;
    glm::vec2 m_pos;
    float m_zoom;

    public:
    Camera();
    Camera(float height, float ar, glm::vec2 pos);

    float getWidth() const;
    float getHeight() const;
    glm::vec2 getPos() const;
    float getZoom() const;

    void setZoom(float zoom);
    void setPos(glm::vec2 pos);
};

class FractalSim
{
    private:
    
    SDL_GLContext gl_context;
    SDL_Window* window;
    unsigned int shader;
    Camera camera;

    bool running;

    public:

    bool init();
    void close();

    void processEvents();
    void render();
};


#endif