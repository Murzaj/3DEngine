#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>

#include "ext/objloader.hpp"

// Updated OBJ loader with texture coordinates and vertex colors.
bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec2> & out_texCoords,
	std::vector<glm::vec3> & out_vertexColors
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices, texCoordIndices, colorIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_texCoords;
	std::vector<glm::vec3> temp_colors;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file! Are you in the right path?\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// Read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// Parse lineHeader
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "vc" ) == 0 ){
			glm::vec3 color;
			fscanf(file, "%f %f %f\n", &color.x, &color.y, &color.z );
			temp_colors.push_back(color);
		}else if ( strcmp( lineHeader, "tt" ) == 0 ){
			glm::vec2 texCoord;
			fscanf(file, "%f %f\n", &texCoord.x, &texCoord.y );
			temp_texCoords.push_back(texCoord);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3], texCoordIndex[3], colorIndex[3];
			int matches = fscanf(file, "%d/%d/%d/%d/%d %d/%d/%d/%d/%d %d/%d/%d/%d/%d\n", 
				&vertexIndex[0], &uvIndex[0], &normalIndex[0], &texCoordIndex[0], &colorIndex[0], 
				&vertexIndex[1], &uvIndex[1], &normalIndex[1], &texCoordIndex[1], &colorIndex[1], 
				&vertexIndex[2], &uvIndex[2], &normalIndex[2], &texCoordIndex[2], &colorIndex[2]);
			if (matches != 15){
				printf("File can't be read by our simple parser :-(\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			texCoordIndices.push_back(texCoordIndex[0]);
			texCoordIndices.push_back(texCoordIndex[1]);
			texCoordIndices.push_back(texCoordIndex[2]);
			colorIndices.push_back(colorIndex[0]);
			colorIndices.push_back(colorIndex[1]);
			colorIndices.push_back(colorIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char buffer[1000];
			fgets(buffer, 1000, file);
		}
	}

	// For each vertex of each triangle
	for( unsigned int i = 0; i < vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		unsigned int texCoordIndex = texCoordIndices[i];
		unsigned int colorIndex = colorIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		glm::vec2 texCoord = temp_texCoords[texCoordIndex - 1];
		glm::vec3 color = temp_colors[colorIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
		out_texCoords.push_back(texCoord);
		out_vertexColors.push_back(color);
	}
	fclose(file);
	return true;
}

