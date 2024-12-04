#include "ModelLoader.hpp"
#include "Shape3D.hpp"

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <unordered_map>

struct FaceData {
  unsigned short vertIdx;
  unsigned short textIdx;
  unsigned short normIdx;
};

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
    outFaces.push_back(f[0].vertIdx);
    outFaces.push_back(f[1].vertIdx);
    outFaces.push_back(f[2].vertIdx);
  }
  std::cout << "Stats:\nV:"<<outVertices.size()<<"\nC:"<<outColors.size()<<"\nF:"<<outFaces.size()<<"\n";
  Shape3D *shape = new Shape3D(outVertices, outColors, outFaces);
  return shape;
}
