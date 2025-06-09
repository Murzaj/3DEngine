#pragma once 

#include <GL/glew.h>
#include <string>
#include "TexturedModelShape3D.hpp" 
#include "ModelShape3D.hpp"        

/// @brief Przestrzeñ nazw zawieraj¹ca funkcje do ³adowania modeli 3D.
///
/// Zawiera funkcje do tworzenia modeli 3D (zarówno z tekstur¹, jak i bez) na podstawie plików OBJ.
/// Modele s¹ zwracane jako wskaŸniki do odpowiednich klas reprezentuj¹cych kszta³ty 3D.
namespace modelloader {

    /// @brief Tworzy obiekt ModelShape3D na podstawie pliku OBJ.
    /// 
    /// Wczytuje model 3D bez tekstury z pliku w formacie OBJ.
    /// @param filename Œcie¿ka do pliku OBJ.
    /// @return WskaŸnik na za³adowany obiekt ModelShape3D.
    ModelShape3D* shapeFromOBJ(const std::string& filename);

    /// @brief Tworzy obiekt TexturedModelShape3D na podstawie pliku OBJ i tekstury.
    /// 
    /// Wczytuje model 3D z tekstur¹ z pliku w formacie OBJ i przypisuje do niego teksturê OpenGL.
    /// @param filename Œcie¿ka do pliku OBJ.
    /// @param textureId Identyfikator tekstury OpenGL.
    /// @return WskaŸnik na za³adowany obiekt TexturedModelShape3D.
    TexturedModelShape3D* texturedShapeFromOBJ(const std::string& filename, GLuint textureId);
}
