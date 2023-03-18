#include "ShaderManager.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>

using namespace rendering;

ShaderManager::ShaderManager() {
    addShader(sBasic, "Shaders/basic.vert", "Shaders/basic.frag");
}

void ShaderManager::addShader(ShaderType name, const char* vertexDir, const char* fragmentDir) {

    //TODO: load source
    std::string vertexShaderSource = loadShaderFromFile(vertexDir);
    std::string fragmentShaderSource = loadShaderFromFile(fragmentDir);

    //compile shaders
    unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    
    //link shaders to program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    //check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(vertexShader, 512, NULL, infoLog);
        printf(infoLog);
    }

    //add to map
    m_shaders.insert(std::pair<ShaderType, unsigned int>(name, shaderProgram));

    //cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int ShaderManager::compileShader(std::string shaderSource, unsigned int type) {

    if (type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
        printf("Invalid Shader Type!");
        return -1;
    }

    if (shaderSource.empty()) {
        return -1;
    }

    const char* source = shaderSource.c_str();

    unsigned int shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        printf(infoLog);
        return -1;
    }

    return shaderID;
    
}

std::string ShaderManager::loadShaderFromFile(const char* dir) {
    std::string code;
    std::ifstream file;
    
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        file.open(dir);
        std::stringstream stream;

        stream << file.rdbuf();

        file.close();

        code = stream.str();

    } catch (std::ifstream::failure e) {
        printf("Error: Shader file not succesfully read!\n");   
        printf(e.what());

    }

    if (!code.empty()) {
        return code.c_str();
    }

    return "";

}

void ShaderManager::useShader(ShaderType name) {
    auto location = m_shaders.find(name);
    if (location != m_shaders.end()) {
         glUseProgram(location->second);
    } else {
        printf("Error: could not find shader!");
        glUseProgram(0);
    }
}