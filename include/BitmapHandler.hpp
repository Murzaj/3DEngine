#pragma once

#include <GL/glew.h>
#include <GL/gl.h> 
#include <string>
#include <unordered_map>

/// @brief Obs�uguje �adowanie, przechowywanie i zarz�dzanie teksturami bitmapowymi w OpenGL.
///
/// Klasa ta umo�liwia �adowanie bitmap z plik�w, dost�p do za�adowanych tekstur
/// oraz ich usuwanie. U�ywana w silniku gry do zarz�dzania zasobami graficznymi.
class BitmapHandler {
public:

    /// @brief �aduje bitmap� z pliku i przypisuje jej nazw�.
    /// 
    /// @param name Nazwa identyfikacyjna tekstury.
    /// @param filename �cie�ka do pliku z bitmap�.
    /// @param magFilter Filtr powi�kszaj�cy (domy�lnie GL_LINEAR).
    /// @param minFilter Filtr pomniejszaj�cy (domy�lnie GL_LINEAR_MIPMAP_LINEAR).
    /// @return ID tekstury OpenGL lub 0 w przypadku b��du.
    GLuint loadBitmap(const std::string& name, const std::string& filename, GLint magFilter = GL_LINEAR, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR);

    /// @brief Zwraca ID tekstury skojarzonej z dan� nazw�.
    /// 
    /// @param name Nazwa identyfikacyjna tekstury.
    /// @return ID tekstury OpenGL lub 0, je�li nie znaleziono.
    GLuint getBitmap(const std::string& name);

    /// @brief Usuwa tekstur� powi�zan� z dan� nazw�.
    /// 
    /// @param name Nazwa tekstury do usuni�cia.
    void removeBitmap(const std::string& name);

    /// @brief Destruktor. Zwalnia wszystkie za�adowane tekstury.
    ~BitmapHandler();

private:
    /// @brief Mapa przechowuj�ca za�adowane tekstury powi�zane z nazwami.
    std::unordered_map<std::string, GLuint> loadedTextures;
};
