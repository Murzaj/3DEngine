#pragma once

#include <glm/glm.hpp> 
#include <vector>

/// @brief Tworzy indeksowane buforowanie wierzcho�k�w.
///
/// Funkcja przekszta�ca dane wej�ciowe modelu (wierzcho�ki, wsp�rz�dne UV i normalne)
/// do postaci zoptymalizowanej za pomoc� indeksowania.
/// Usuwa duplikaty i generuje wektory unikalnych danych oraz odpowiadaj�ce im indeksy.
///
/// @param in_vertices Wektor wej�ciowy z pozycjami wierzcho�k�w.
/// @param in_uvs Wektor wej�ciowy z wsp�rz�dnymi tekstury (UV).
/// @param in_normals Wektor wej�ciowy z wektorami normalnymi.
/// @param out_indices Wektor wyj�ciowy, do kt�rego zostan� zapisane indeksy.
/// @param out_vertices Wektor wyj�ciowy z unikalnymi pozycjami wierzcho�k�w.
/// @param out_uvs Wektor wyj�ciowy z unikalnymi wsp�rz�dnymi UV.
/// @param out_normals Wektor wyj�ciowy z unikalnymi wektorami normalnymi.
void indexVBO(
    std::vector<glm::vec3>& in_vertices,
    std::vector<glm::vec2>& in_uvs,
    std::vector<glm::vec3>& in_normals,

    std::vector<unsigned short>& out_indices,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
);
