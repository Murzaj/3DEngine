#include "ModelLoader.hpp"
#include "ext/objloader.hpp"
#include "ext/vboindexer.hpp"

#include <glm/glm.hpp>
#include <string>

struct FaceData {
  unsigned short vertIdx;
  unsigned short textIdx;
  unsigned short normIdx;
};



struct ModelData {
  std::vector<float> vertices; 
  std::vector<float> normals; 
  std::vector<unsigned int> indices; 
  std::vector<float> uvs; 
};


ModelData load(const std::string &filename) {
  std::vector<glm::vec3> orig_vertices;
  std::vector<glm::vec2> orig_uvs;
  std::vector<glm::vec3> orig_normals;

  loadOBJ(filename.c_str(), orig_vertices, orig_uvs, orig_normals);

  std::vector<glm::vec3> out_vertices;
  std::vector<glm::vec2> out_uvs;
  std::vector<glm::vec3> out_normals;
  std::vector<unsigned short> out_indices;
  indexVBO(orig_vertices, orig_uvs, orig_normals, out_indices, out_vertices, out_uvs, out_normals);

  ModelData d;

  for (glm::vec3 v : out_vertices) {
    d.vertices.push_back(v.x);
    d.vertices.push_back(v.y);
    d.vertices.push_back(v.z);
  }
  for (glm::vec3 n : out_normals) {
    d.normals.push_back(n.x);
    d.normals.push_back(n.y);
    d.normals.push_back(n.z);
  }

  for (glm::vec2 u : out_uvs) {
    d.uvs.push_back(u.x);
    d.uvs.push_back(u.y);
  }

  for (unsigned short i : out_indices) {
    d.indices.push_back(i);
  }
  return d;
}

TexturedModelShape3D *modelloader::texturedShapeFromOBJ(const std::string &filename, GLuint textureId) {
  ModelData d = load(filename);
  return new TexturedModelShape3D(d.vertices, {}, glm::vec3(1.0f), d.normals, d.indices, d.uvs, textureId);
}

ModelShape3D *modelloader::shapeFromOBJ(const std::string &filename) {
  ModelData d = load(filename);
  return new ModelShape3D(d.vertices, {}, glm::vec3(1.0f), d.normals, d.indices, d.uvs);
}


