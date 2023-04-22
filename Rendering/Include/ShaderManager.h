#pragma once
#include <unordered_map>
#include <string>
#include <glm/ext/matrix_float4x4.hpp>
namespace rendering {
    typedef enum ShaderType {
        sBasic,
        sLighted
    } ShaderType;

class ShaderManager
{
public:
    ShaderManager();
    void addShader(ShaderType name, const char* vertexDir, const char* fragmentDir);
    void useShader(ShaderType name);
    void bindAttribute(ShaderType id, const std::string& name, glm::mat4 data) const;
protected:
    int compileShader(std::string shaderSource, unsigned int type);
    std::string loadShaderFromFile(const char* dir);
private:
    std::unordered_map<ShaderType, unsigned int> m_shaders;
};
}

