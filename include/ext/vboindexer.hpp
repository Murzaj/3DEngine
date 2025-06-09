#pragma once

#include <glm/glm.hpp> 
#include <vector>

/// @brief Tworzy indeksowane buforowanie wierzcho³ków.
///
/// Funkcja przekszta³ca dane wejœciowe modelu (wierzcho³ki, wspó³rzêdne UV i normalne)
/// do postaci zoptymalizowanej za pomoc¹ indeksowania.
/// Usuwa duplikaty i generuje wektory unikalnych danych oraz odpowiadaj¹ce im indeksy.
///
/// @param in_vertices Wektor wejœciowy z pozycjami wierzcho³ków.
/// @param in_uvs Wektor wejœciowy z wspó³rzêdnymi tekstury (UV).
/// @param in_normals Wektor wejœciowy z wektorami normalnymi.
/// @param out_indices Wektor wyjœciowy, do którego zostan¹ zapisane indeksy.
/// @param out_vertices Wektor wyjœciowy z unikalnymi pozycjami wierzcho³ków.
/// @param out_uvs Wektor wyjœciowy z unikalnymi wspó³rzêdnymi UV.
/// @param out_normals Wektor wyjœciowy z unikalnymi wektorami normalnymi.
void indexVBO(
    std::vector<glm::vec3>& in_vertices,
    std::vector<glm::vec2>& in_uvs,
    std::vector<glm::vec3>& in_normals,

    std::vector<unsigned short>& out_indices,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
);
