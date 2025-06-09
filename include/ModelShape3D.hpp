#pragma once

#include <GL/glew.h> 
#include <vector>
#include <glm/glm.hpp> 
#include "Shape3D.hpp" 

/// @brief Klasa reprezentuj¹ca model 3D z geometri¹ i opcjonaln¹ tekstur¹.
///
/// Przechowuje dane o wierzcho³kach, kolorach, normalnych, wspó³rzêdnych tekstury oraz indeksach.
/// Umo¿liwia rysowanie modelu z uwzglêdnieniem koloru moduluj¹cego i tekstury.
class ModelShape3D : public Shape3D {
protected:
    std::vector<float> verts;           ///< Wspó³rzêdne wierzcho³ków.
    std::vector<float> colors;          ///< Kolory przypisane do wierzcho³ków.
    std::vector<float> normals;         ///< Wektory normalne dla oœwietlenia.
    std::vector<float> texCoords;       ///< Wspó³rzêdne tekstury.

    std::vector<unsigned int> indices;  ///< Indeksy wierzcho³ków (dla rysowania indeksowanego).

    glm::vec3 modulateColor;            ///< Kolor moduluj¹cy (mno¿ony przez kolor tekstury lub materia³u).

    GLuint textureId = 0;               ///< Identyfikator tekstury OpenGL.

public:

    /// @brief Konstruktor modelu 3D.
    ///
    /// Inicjalizuje dane modelu, w tym geometriê, kolory, normalne, indeksy oraz teksturê.
    /// @param verts Wierzcho³ki modelu.
    /// @param colors Kolory przypisane do wierzcho³ków.
    /// @param modulateColor Kolor moduluj¹cy modelu.
    /// @param normals Normalne do oœwietlenia.
    /// @param indices Indeksy wierzcho³ków.
    /// @param texCoord Wspó³rzêdne tekstury.
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

    /// @brief Rysuje model 3D z uwzglêdnieniem widoku.
    /// @param view Macierz widoku (np. z kamery).
    virtual void draw(const glm::mat4& view) override;

    /// @brief Ustawia teksturê dla modelu.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) override;
};
