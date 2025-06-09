#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje kolorow� p�ask� powierzchni� 3D.
///
/// Klasa s�u�y do renderowania p�askiej powierzchni z nadanym kolorem.
/// Wy��cza o�wietlenie OpenGL podczas rysowania, aby uzyska� jednolity kolor.
class ColoredPlane3D : public PrimitiveShape3D {
public:

    /// @brief Konstruktor tworz�cy p�aszczyzn� z okre�lonym kolorem.
    /// @param color Kolor p�aszczyzny jako wektor RGB.
    explicit ColoredPlane3D(const glm::vec3& color)
        : PrimitiveShape3D(color) {
    }

    /// @brief Rysuje obiekt z wy��czonym o�wietleniem (czysty kolor).
    /// @param view Macierz widoku u�ywana do renderowania.
    virtual void draw(const glm::mat4& view) override {
        // wy��cz o�wietlenie, rysuj czystym kolorem
        glDisable(GL_LIGHTING);
        PrimitiveShape3D::draw(view);
        // przywr��
        glEnable(GL_LIGHTING);
    }

protected:

    /// @brief Implementacja w�a�ciwego rysowania geometrii p�aszczyzny.
    ///
    /// Tworzy kwadratow� p�aszczyzn� w uk�adzie XZ o wymiarach 2x2, po�o�on� na Y = 0.
    virtual void primitiveDrawingFunc() override {
        glBegin(GL_QUADS);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, 0.0f, 1.0f);
        glEnd();
    }
};
