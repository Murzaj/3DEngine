#pragma once

#include <GL/glew.h> 
#include <glm/glm.hpp>
#include "Shape3D.hpp"

/// @brief Bazowa klasa dla prymitywnych kszta³tów 3D.
///
/// Reprezentuje obiekt 3D rysowany za pomoc¹ prymitywów OpenGL (np. sfery, kostki, sto¿ki).
/// Pozwala na ustawienie koloru i tekstury oraz wymaga implementacji funkcji rysuj¹cej konkretny prymityw.
class PrimitiveShape3D : public Shape3D {
protected:
	glm::vec3 color;     ///< Kolor obiektu.
	GLuint texture = 0;  ///< Identyfikator tekstury OpenGL.

	/// @brief Czysto wirtualna funkcja rysuj¹ca prymityw.
	///
	/// Funkcja musi zostaæ zaimplementowana przez klasy pochodne w celu wykonania odpowiednich poleceñ OpenGL.
	virtual void primitiveDrawingFunc() = 0;

public:
	/// @brief Konstruktor ustawiaj¹cy kolor prymitywu.
	/// @param color Kolor obiektu 3D.
	PrimitiveShape3D(const glm::vec3& color) : color(color), texture(0) {}

	/// @brief Wirtualny destruktor.
	virtual ~PrimitiveShape3D() = default;

	/// @brief Rysuje obiekt w przestrzeni 3D.
	/// @param view Macierz widoku u¿ywana do transformacji sceny.
	virtual void draw(const glm::mat4& view) override;

	/// @brief Ustawia teksturê dla obiektu.
	/// @param textureId Identyfikator tekstury OpenGL.
	virtual void setTexture(GLuint textureId) override { this->texture = textureId; }
};
