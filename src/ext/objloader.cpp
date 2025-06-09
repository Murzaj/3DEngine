#include <vector>
#include <stdio.h>
#include <string>
#include <cstring> 
#include <glm/glm.hpp>
#include "ext/objloader.hpp" 
#include <iostream> 


bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
) {
	std::cout << "Ladowanie pliku OBJ: " << path << "..." << std::endl;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE* file = fopen(path, "r");
	if (file == NULL) {
		std::cerr << "Blad: Nie mozna otworzyc pliku! Sciezka: " << path << std::endl;
		return false;
	}


	while (1) {

		char lineHeader[128];
	
		int res = fscanf(file, "%127s", lineHeader);
		if (res == EOF)
			break; 



		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
		
			if (fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z) != 3) {
				std::cerr << "Blad odczytu danych wierzcholka w " << path << std::endl;
				fclose(file);
				return false;
			}
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
		
			if (fscanf(file, "%f %f\n", &uv.x, &uv.y) != 2) {
				std::cerr << "Blad odczytu danych wspolrzednych tekstury w " << path << std::endl;
				fclose(file);
				return false;
			}
	
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
		
			if (fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z) != 3) {
				std::cerr << "Blad odczytu danych w " << path << std::endl;
				fclose(file);
				return false;
			}
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
		
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9) {
				
				std::cerr << "Blad: Plik nie moze zostac odczytany. Sciezka: " << path << std::endl;

		
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);

	
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
		}
		else {
	
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	fclose(file); 


	out_vertices.reserve(vertexIndices.size());
	out_uvs.reserve(vertexIndices.size());
	out_normals.reserve(vertexIndices.size());

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {


		unsigned int vIdx = vertexIndices[i];
		unsigned int uvIdx = uvIndices[i];
		unsigned int nIdx = normalIndices[i];


		if (vIdx == 0 || vIdx > temp_vertices.size() ||
			uvIdx == 0 || uvIdx > temp_uvs.size() ||
			nIdx == 0 || nIdx > temp_normals.size()) {
			std::cerr << "Blad: Znaleziono nieprawidlowy indeks v:" << vIdx << " uv:" << uvIdx << " n:" << nIdx << " Sciezka: " << path << std::endl;
			return false; 
		}


		glm::vec3 vertex = temp_vertices[vIdx - 1];
		glm::vec2 uv = temp_uvs[uvIdx - 1];
		glm::vec3 normal = temp_normals[nIdx - 1];


		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}

	std::cout << "Ladowanie OBJ zakonczone. Przetworzone wierzcholki: " << out_vertices.size() << std::endl;
	return true; 
}

