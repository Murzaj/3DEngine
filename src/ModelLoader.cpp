#include "ModelLoader.hpp"
#include "ext/objloader.hpp"  
#include "ext/vboindexer.hpp" 

#include <glm/glm.hpp>
#include <vector>
#include <iostream> 


struct IndexedModelData {
    std::vector<float> vertices; 
    std::vector<float> normals;  
    std::vector<float> uvs;      
    std::vector<unsigned int> indices; 
};

IndexedModelData loadAndIndexOBJ(const std::string& filename) {
    IndexedModelData data; 


    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    bool loadSuccess = loadOBJ(filename.c_str(), temp_vertices, temp_uvs, temp_normals);

    if (!loadSuccess) {
        std::cerr << "Nie udalo siê zaladowac pliku OBJ: " << filename << std::endl;
        return data; 
    }


    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    std::vector<unsigned short> indexed_indices_short; 


    indexVBO(temp_vertices, temp_uvs, temp_normals,
        indexed_indices_short, indexed_vertices, indexed_uvs, indexed_normals);

    data.vertices.reserve(indexed_vertices.size() * 3);
    for (const auto& v : indexed_vertices) {
        data.vertices.push_back(v.x);
        data.vertices.push_back(v.y);
        data.vertices.push_back(v.z);
    }


    data.normals.reserve(indexed_normals.size() * 3);
    for (const auto& n : indexed_normals) {
        data.normals.push_back(n.x);
        data.normals.push_back(n.y);
        data.normals.push_back(n.z);
    }


    data.uvs.reserve(indexed_uvs.size() * 2);
    for (const auto& uv : indexed_uvs) {
        data.uvs.push_back(uv.x);
        data.uvs.push_back(uv.y);
    }


    data.indices.reserve(indexed_indices_short.size());
    for (unsigned short index : indexed_indices_short) {
        data.indices.push_back(static_cast<unsigned int>(index));
    }

    std::cout << "Zaladowano i zindeksowano '" << filename << "'. Wierzcholki: " << data.vertices.size() / 3 << ", Indeksy: " << data.indices.size() << std::endl;
    return data;
}




namespace modelloader {


    TexturedModelShape3D* texturedShapeFromOBJ(const std::string& filename, GLuint textureId) {
        IndexedModelData d = loadAndIndexOBJ(filename);
        if (d.vertices.empty()) return nullptr; 

        return new TexturedModelShape3D(
            d.vertices,
            {}, 
            glm::vec3(1.0f), 
            d.normals,
            d.indices,
            d.uvs,
            textureId 
        );
    }

    ModelShape3D* shapeFromOBJ(const std::string& filename) {
        IndexedModelData d = loadAndIndexOBJ(filename);
        if (d.vertices.empty()) return nullptr; 

        return new ModelShape3D(
            d.vertices,
            {}, 
            glm::vec3(1.0f), 
            d.normals,
            d.indices,
            d.uvs
        );
    }

} 
