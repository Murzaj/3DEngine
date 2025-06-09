#pragma once

#include <GL/glew.h> 
#include <vector>
#include <glm/glm.hpp> 
#include "Shape3D.hpp" 

/// @brief Klasa reprezentuj�ca model 3D z geometri� i opcjonaln� tekstur�.
///
/// Przechowuje dane o wierzcho�kach, kolorach, normalnych, wsp�rz�dnych tekstury oraz indeksach.
/// Umo�liwia rysowanie modelu z uwzgl�dnieniem koloru moduluj�cego i tekstury.
class ModelShape3D : public Shape3D {
protected:
    std::vector<float> verts;           ///< Wsp�rz�dne wierzcho�k�w.
    std::vector<float> colors;          ///< Kolory przypisane do wierzcho�k�w.
    std::vector<float> normals;         ///< Wektory normalne dla o�wietlenia.
    std::vector<float> texCoords;       ///< Wsp�rz�dne tekstury.

    std::vector<unsigned int> indices;  ///< Indeksy wierzcho�k�w (dla rysowania indeksowanego).

    glm::vec3 modulateColor;            ///< Kolor moduluj�cy (mno�ony przez kolor tekstury lub materia�u).

    GLuint textureId = 0;               ///< Identyfikator tekstury OpenGL.

public:

    /// @brief Konstruktor modelu 3D.
    ///
    /// Inicjalizuje dane modelu, w tym geometri�, kolory, normalne, indeksy oraz tekstur�.
    /// @param verts Wierzcho�ki modelu.
    /// @param colors Kolory przypisane do wierzcho�k�w.
    /// @param modulateColor Kolor moduluj�cy modelu.
    /// @param normals Normalne do o�wietlenia.
    /// @param indices Indeksy wierzcho�k�w.
    /// @param texCoord Wsp�rz�dne tekstury.
    ModelShape3D(
        const std::vector<float>& verts,
        const std::vector<float>& colors,
        glm::vec3 modulateColor,
        const std::vector<float>& normals,
        const std::vector<unsigned int>& indices,
        const std::vector<float>& texCoord
    );

    /// @brief Wirtualny destruktor.
    virtual ~ModelShape3D() = default;

    /// @brief Rysuje model 3D z uwzgl�dnieniem widoku.
    /// @param view Macierz widoku (np. z kamery).
    virtual void draw(const glm::mat4& view) override;

    /// @brief Ustawia tekstur� dla modelu.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) override;
};
