#pragma once

#include <vector>
#include <string>

namespace glm {
    template<length_t L, typename T, qualifier Q> struct vec;
    using vec2 = vec<2, float, defaultp>;
    using vec3 = vec<3, float, defaultp>;
}

/// @brief Wczytuje model 3D z pliku w formacie OBJ.
///
/// Funkcja odczytuje dane wierzcho�k�w, wsp�rz�dnych UV oraz wektor�w normalnych z pliku .obj
/// i zapisuje je do podanych wektor�w wyj�ciowych.
///
/// @param path �cie�ka do pliku OBJ.
/// @param out_vertices Referencja do wektora, do kt�rego zostan� zapisane pozycje wierzcho�k�w.
/// @param out_uvs Referencja do wektora, do kt�rego zostan� zapisane wsp�rz�dne tekstury (UV).
/// @param out_normals Referencja do wektora, do kt�rego zostan� zapisane wektory normalne.
/// @return true je�li plik zosta� poprawnie wczytany, w przeciwnym razie false.
bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
);
