#pragma once 

#include <GL/glew.h>
#include <string>
#include "TexturedModelShape3D.hpp" 
#include "ModelShape3D.hpp"        

/// @brief Przestrze� nazw zawieraj�ca funkcje do �adowania modeli 3D.
///
/// Zawiera funkcje do tworzenia modeli 3D (zar�wno z tekstur�, jak i bez) na podstawie plik�w OBJ.
/// Modele s� zwracane jako wska�niki do odpowiednich klas reprezentuj�cych kszta�ty 3D.
namespace modelloader {

    /// @brief Tworzy obiekt ModelShape3D na podstawie pliku OBJ.
    /// 
    /// Wczytuje model 3D bez tekstury z pliku w formacie OBJ.
    /// @param filename �cie�ka do pliku OBJ.
    /// @return Wska�nik na za�adowany obiekt ModelShape3D.
    ModelShape3D* shapeFromOBJ(const std::string& filename);

    /// @brief Tworzy obiekt TexturedModelShape3D na podstawie pliku OBJ i tekstury.
    /// 
    /// Wczytuje model 3D z tekstur� z pliku w formacie OBJ i przypisuje do niego tekstur� OpenGL.
    /// @param filename �cie�ka do pliku OBJ.
    /// @param textureId Identyfikator tekstury OpenGL.
    /// @return Wska�nik na za�adowany obiekt TexturedModelShape3D.
    TexturedModelShape3D* texturedShapeFromOBJ(const std::string& filename, GLuint textureId);
}
