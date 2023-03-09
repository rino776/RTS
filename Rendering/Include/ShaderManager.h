#pragma once
#include <unordered_map>
#include <string>
namespace rendering {
    typedef enum ShaderType {
        sBasic
    } ShaderType;

class ShaderManager
{
public:
    ShaderManager();
    void addShader(ShaderType name, const char* vertexDir, const char* fragmentDir);
    void useShader(ShaderType name);
protected:
    int compileShader(std::string shaderSource, unsigned int type);
    std::string loadShaderFromFile(const char* dir);
private:
    std::unordered_map<ShaderType, unsigned int> m_shaders;
};
}

