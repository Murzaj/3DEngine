#include "ModelLoader.hpp"
#include "Shape3D.hpp"
#include "ext/objloader.hpp"
#include "ext/vboindexer.hpp"

#include <glm/glm.hpp>
#include <string>

struct FaceData {
  unsigned short vertIdx;
  unsigned short textIdx;
  unsigned short normIdx;
};

/*
Shape3D *modelloader::shapeFromOBJ(const std::string &filename) {
  std::fstream file;


  std::cout << "[ModelLoader] Opening " << filename << " ...\n";
  file.open(filename);

  if(!file.is_open()) {
    std::cerr << "[ModelLoader] File " << filename << " could not be opened!\n";
    return NULL;
  }


  std::vector<std::array<FaceData, 3>> faces;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> colors;

  std::string line;
  while (std::getline(file, line)) {
    if(line.empty()) continue;

    std::istringstream stream(line);

    std::string type;
    stream >> type;
    if(type == "v") {
      float x, y, z;
      stream >> x >> y >> z;
      vertices.push_back(glm::vec3(x,y,z));
      stream >> x >> y >> z;
      colors.push_back(glm::vec3(x,y,z));
    }
    if(type == "f") {
      char separator;

      std::array<FaceData,3> tris;
      for(int i = 0; i < 3; i++) {
        stream >> tris[i].vertIdx >> separator >> tris[i].textIdx >> separator >> tris[i].normIdx;
      }
      faces.push_back(tris);
    }
  }


  std::vector<float> outVertices;
  std::vector<float> outColors;
  std::vector<unsigned int> outFaces;

  for (auto v : vertices) {
    outVertices.push_back(v.x);
    outVertices.push_back(v.y);
    outVertices.push_back(v.z);
  }
  for (auto c : colors) {
    outColors.push_back(c.r);
    outColors.push_back(c.g);
    outColors.push_back(c.b);
  }

  for (auto f : faces) {
    outFaces.push_back(f[0].vertIdx-1);
    outFaces.push_back(f[1].vertIdx-1);
    outFaces.push_back(f[2].vertIdx-1);
  }


  std::vector<float> outNormals;
  std::vector<float> outTexCoord;
  std::cout << "Stats:\nV:"<<outVertices.size()<<"\nF:"<<outFaces.size()/3<<"\n";
  Shape3D *shape = new Shape3D(outVertices, outColors, outNormals, outFaces, outTexCoord);
  return shape;
}
*/


Shape3D *modelloader::shapeFromOBJGenerated(const std::string &filename) {
  std::vector<glm::vec3> orig_vertices;
  std::vector<glm::vec2> orig_uvs;
  std::vector<glm::vec3> orig_normals;

  loadOBJ(filename.c_str(), orig_vertices, orig_uvs, orig_normals);

  std::vector<glm::vec3> out_vertices;
  std::vector<glm::vec2> out_uvs;
  std::vector<glm::vec3> out_normals;
  std::vector<unsigned short> out_indices;
  indexVBO(orig_vertices, orig_uvs, orig_normals, out_indices, out_vertices, out_uvs, out_normals);

  std::vector<float> final_vertices; 
  std::vector<float> final_normals; 
  std::vector<unsigned int> final_indices; 
  std::vector<float> final_uvs; 

  for (glm::vec3 v : out_vertices) {
    final_vertices.push_back(v.x);
    final_vertices.push_back(v.y);
    final_vertices.push_back(v.z);
  }
  for (glm::vec3 n : out_normals) {
    final_normals.push_back(n.x);
    final_normals.push_back(n.y);
    final_normals.push_back(n.z);
  }

  for (glm::vec2 u : out_uvs) {
    final_uvs.push_back(u.x);
    final_uvs.push_back(u.y);
  }

  for (unsigned short i : out_indices) {
    final_indices.push_back(i);
  }

  return new Shape3D(final_vertices, {}, final_normals, final_indices, final_uvs);
}


