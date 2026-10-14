#include "helpers.hpp"

bool init(SDL_Window*& w)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Could not initialize video! SDL error: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                   SDL_GL_CONTEXT_PROFILE_CORE);

    w = SDL_CreateWindow(
        "Learning OpenGL",
        800,
        600,
        SDL_WINDOW_OPENGL
    );

    if (w == nullptr)
    {
        SDL_Log("Could not initialize window! SDL error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close(SDL_Window*& w)
{
    if (w != nullptr)
    {
        SDL_DestroyWindow(w);
        w = nullptr;
    }

    SDL_Quit();
}

std::string getCodeFromFile(std::string path)
{
    std::string code;
    std::fstream file;

    try
    {
        file.open(path.c_str());

        std::stringstream code_stream;

        code_stream << file.rdbuf();

        file.close();

        code = code_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return code;
}

unsigned int setUpShaders(
    const char* v_shader_source, const char* f_shader_source
)
{
    int success;
    char infoLog[512];

    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &v_shader_source, NULL);
    glCompileShader(v_shader);
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(v_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &f_shader_source, NULL);
    glCompileShader(f_shader);
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(f_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }    

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, v_shader);
    glAttachShader(shader_program, f_shader);
    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKIN_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    return shader_program;
}