#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "ext/vboindexer.hpp" 
#include <string.h> 
#include <iostream> 


struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;


	bool operator<(const PackedVertex that) const {

		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};


bool getSimilarVertexIndex_fast(
	PackedVertex& packed,
	std::map<PackedVertex, unsigned short>& VertexToOutIndex, 
	unsigned short& result 
) {
	auto it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {

		return false;
	}
	else {
		
		result = it->second;
		return true;
	}
}


void indexVBO(
	std::vector<glm::vec3>& in_vertices, 
	std::vector<glm::vec2>& in_uvs,     
	std::vector<glm::vec3>& in_normals,  

	std::vector<unsigned short>& out_indices, 
	std::vector<glm::vec3>& out_vertices,    
	std::vector<glm::vec2>& out_uvs,          
	std::vector<glm::vec3>& out_normals      
) {

	std::map<PackedVertex, unsigned short> VertexToOutIndex;

	out_indices.clear();
	out_vertices.clear();
	out_uvs.clear();
	out_normals.clear();


	out_indices.reserve(in_vertices.size());
	out_vertices.reserve(in_vertices.size()); 
	out_uvs.reserve(in_vertices.size());
	out_normals.reserve(in_vertices.size());


	for (unsigned int i = 0; i < in_vertices.size(); i++) {


		PackedVertex packed = {
			in_vertices[i],
			(i < in_uvs.size() ? in_uvs[i] : glm::vec2(0.0f)), 
			(i < in_normals.size() ? in_normals[i] : glm::vec3(0.0f, 1.0f, 0.0f)) 
		};

	
		unsigned short index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) {
			
		
			out_indices.push_back(index);
		}
		else {
			
			out_vertices.push_back(packed.position);
			out_uvs.push_back(packed.uv);
			out_normals.push_back(packed.normal);

			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(newindex);

		
			VertexToOutIndex[packed] = newindex;
		}
	}
}