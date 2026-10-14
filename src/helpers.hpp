#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

bool init(SDL_Window*& w);
void close(SDL_Window*& w);

std::string getCodeFromFile(std::string path);
unsigned int setUpShaders(
    const char* v_shader_source, const char* f_shader_source
);

#endif