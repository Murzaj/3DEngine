#pragma once

#include <GL/glew.h> 
#include <vector>   
#include <glm/glm.hpp> 
#include "ModelShape3D.hpp" 

/// @brief Klasa reprezentuj�ca tr�jwymiarowy model z tekstur�.
/// 
/// Dziedziczy po ModelShape3D i rozszerza funkcjonalno�� o obs�ug� tekstur.
class TexturedModelShape3D : public ModelShape3D {

public:

    /// @brief Konstruktor klasy TexturedModelShape3D.
    /// @param verts Wektor wsp�rz�dnych wierzcho�k�w modelu.
    /// @param colors Wektor kolor�w wierzcho�k�w.
    /// @param modulateColor Kolor moduluj�cy (mno�nik koloru).
    /// @param normals Wektor wektor�w normalnych do powierzchni.
    /// @param indices Wektor indeks�w do rysowania element�w modelu.
    /// @param texCoord Wektor wsp�rz�dnych tekstury.
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

    /// @brief Domy�lny destruktor.
    virtual ~TexturedModelShape3D() = default;

    /// @brief Metoda rysuj�ca model z uwzgl�dnieniem tekstury.
    /// @param view Macierz widoku u�ywana do renderowania.
    virtual void draw(const glm::mat4& view) override;

    /// @brief Ustawia tekstur� modelu.
    /// @param texture Identyfikator tekstury OpenGL.
    virtual void setTexture(GLuint texture) override;
};
