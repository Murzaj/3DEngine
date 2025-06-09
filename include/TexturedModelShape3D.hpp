#pragma once

#include <GL/glew.h> 
#include <vector>   
#include <glm/glm.hpp> 
#include "ModelShape3D.hpp" 

/// @brief Klasa reprezentuj¹ca trójwymiarowy model z tekstur¹.
/// 
/// Dziedziczy po ModelShape3D i rozszerza funkcjonalnoœæ o obs³ugê tekstur.
class TexturedModelShape3D : public ModelShape3D {

public:

    /// @brief Konstruktor klasy TexturedModelShape3D.
    /// @param verts Wektor wspó³rzêdnych wierzcho³ków modelu.
    /// @param colors Wektor kolorów wierzcho³ków.
    /// @param modulateColor Kolor moduluj¹cy (mno¿nik koloru).
    /// @param normals Wektor wektorów normalnych do powierzchni.
    /// @param indices Wektor indeksów do rysowania elementów modelu.
    /// @param texCoord Wektor wspó³rzêdnych tekstury.
    /// @param textureId Identyfikator tekstury OpenGL.
    TexturedModelShape3D(
        const std::vector<float>& verts,
        const std::vector<float>& colors,
        glm::vec3 modulateColor,
        const std::vector<float>& normals,
        const std::vector<unsigned int>& indices,
        const std::vector<float>& texCoord,
        GLuint textureId
    );

    /// @brief Domyœlny destruktor.
    virtual ~TexturedModelShape3D() = default;

    /// @brief Metoda rysuj¹ca model z uwzglêdnieniem tekstury.
    /// @param view Macierz widoku u¿ywana do renderowania.
    virtual void draw(const glm::mat4& view) override;

    /// @brief Ustawia teksturê modelu.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) override;
};
