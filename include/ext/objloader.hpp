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
/// Funkcja odczytuje dane wierzcho³ków, wspó³rzêdnych UV oraz wektorów normalnych z pliku .obj
/// i zapisuje je do podanych wektorów wyjœciowych.
///
/// @param path Œcie¿ka do pliku OBJ.
/// @param out_vertices Referencja do wektora, do którego zostan¹ zapisane pozycje wierzcho³ków.
/// @param out_uvs Referencja do wektora, do którego zostan¹ zapisane wspó³rzêdne tekstury (UV).
/// @param out_normals Referencja do wektora, do którego zostan¹ zapisane wektory normalne.
/// @return true jeœli plik zosta³ poprawnie wczytany, w przeciwnym razie false.
bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
);
