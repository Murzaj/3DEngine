#pragma once

#include <glm/glm.hpp>
#include <vector>

void indexVBO(
	std::vector<glm::vec3> &in_vertices,
	std::vector<glm::vec2> &in_uvs,
	std::vector<glm::vec3> &in_normals,
	std::vector<unsigned short> &out_indices,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals
);

