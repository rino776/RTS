#include "ObjLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <Point.h>

using namespace loader;
using namespace core;

Mesh* ObjLoader::loadFromFile(const char* path) {
    std::string line;
    std::ifstream file (path);

    std::vector<Point> vertices;
    std::vector<unsigned int> indices;

    if (file.is_open()) {
        while (getline(file, line)) {
            
            //if it starts with a # it is a comment, and we can ignore the line
            if (line[0] == '#')
                continue;
            
            //it is a vertex, add it to the vertex list
            if (line[0] == 'v') {
                //remove the v from the beginning
                line = line.substr(2);
                float x = std::stof(line.substr(0, line.find(' ')));
                line = line.substr(line.find(' ') + 1);
                float y = std::stof(line.substr(0, line.find(' ')));
                line = line.substr(line.find(' ') + 1);
                float z = std::stof(line.substr(0, line.find(' ')));
                line = line.substr(line.find(' ') + 1);
                
                vertices.push_back(Point(x, y, z));
                continue;
            }

            if (line[0] == 'f') {
                //remove the f from the beginning
                line = line.substr(2);
                //check if it has multiple parameters
                std::size_t index = line.find('/');

                //no normals or uvs, only the index found
                if (index == std::string::npos) {
                    //assume 3 vertices per face
                    unsigned int i = std::stoul(line.substr(0, line.find(' ')));
                    line = line.substr(line.find(' ') + 1);
                    //indices are not 0 indexed...
                    indices.push_back(i - 1);

                    i = std::stoul(line.substr(0, line.find(' ')));
                    line = line.substr(line.find(' ') + 1);
                    indices.push_back(i - 1);
                    
                    i = std::stoul(line.substr(0, line.find(' ')));
                    line = line.substr(line.find(' ') + 1);
                    indices.push_back(i - 1);
                }
            }
                
        }


        file.close();
    }
    else {
        printf("Can't open file!\nPath: ");
        printf(path);
    }

    return new Mesh(vertices, indices);

}
