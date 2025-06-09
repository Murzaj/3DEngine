#pragma once

#include <GL/glew.h>
#include <GL/gl.h> 
#include <string>
#include <unordered_map>

/// @brief Obs³uguje ³adowanie, przechowywanie i zarz¹dzanie teksturami bitmapowymi w OpenGL.
///
/// Klasa ta umo¿liwia ³adowanie bitmap z plików, dostêp do za³adowanych tekstur
/// oraz ich usuwanie. U¿ywana w silniku gry do zarz¹dzania zasobami graficznymi.
class BitmapHandler {
public:

    /// @brief £aduje bitmapê z pliku i przypisuje jej nazwê.
    /// 
    /// @param name Nazwa identyfikacyjna tekstury.
    /// @param filename Œcie¿ka do pliku z bitmap¹.
    /// @param magFilter Filtr powiêkszaj¹cy (domyœlnie GL_LINEAR).
    /// @param minFilter Filtr pomniejszaj¹cy (domyœlnie GL_LINEAR_MIPMAP_LINEAR).
    /// @return ID tekstury OpenGL lub 0 w przypadku b³êdu.
    GLuint loadBitmap(const std::string& name, const std::string& filename, GLint magFilter = GL_LINEAR, GLint minFilter = GL_LINEAR_MIPMAP_LINEAR);

    /// @brief Zwraca ID tekstury skojarzonej z dan¹ nazw¹.
    /// 
    /// @param name Nazwa identyfikacyjna tekstury.
    /// @return ID tekstury OpenGL lub 0, jeœli nie znaleziono.
    GLuint getBitmap(const std::string& name);

    /// @brief Usuwa teksturê powi¹zan¹ z dan¹ nazw¹.
    /// 
    /// @param name Nazwa tekstury do usuniêcia.
    void removeBitmap(const std::string& name);

    /// @brief Destruktor. Zwalnia wszystkie za³adowane tekstury.
    ~BitmapHandler();

private:
    /// @brief Mapa przechowuj¹ca za³adowane tekstury powi¹zane z nazwami.
    std::unordered_map<std::string, GLuint> loadedTextures;
};
