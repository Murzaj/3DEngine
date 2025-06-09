#pragma once

#include "PrimitiveShape3D.hpp"
#include <GL/glut.h>

/// @brief Reprezentuje kolorow¹ p³ask¹ powierzchniê 3D.
///
/// Klasa s³u¿y do renderowania p³askiej powierzchni z nadanym kolorem.
/// Wy³¹cza oœwietlenie OpenGL podczas rysowania, aby uzyskaæ jednolity kolor.
class ColoredPlane3D : public PrimitiveShape3D {
public:

    /// @brief Konstruktor tworz¹cy p³aszczyznê z okreœlonym kolorem.
    /// @param color Kolor p³aszczyzny jako wektor RGB.
    explicit ColoredPlane3D(const glm::vec3& color)
        : PrimitiveShape3D(color) {
    }

    /// @brief Rysuje obiekt z wy³¹czonym oœwietleniem (czysty kolor).
    /// @param view Macierz widoku u¿ywana do renderowania.
    virtual void draw(const glm::mat4& view) override {
        // wy³¹cz oœwietlenie, rysuj czystym kolorem
        glDisable(GL_LIGHTING);
        PrimitiveShape3D::draw(view);
        // przywróæ
        glEnable(GL_LIGHTING);
    }

protected:

    /// @brief Implementacja w³aœciwego rysowania geometrii p³aszczyzny.
    ///
    /// Tworzy kwadratow¹ p³aszczyznê w uk³adzie XZ o wymiarach 2x2, po³o¿on¹ na Y = 0.
    virtual void primitiveDrawingFunc() override {
        glBegin(GL_QUADS);
        glVertex3f(-1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f, -1.0f);
        glVertex3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-1.0f, 0.0f, 1.0f);
        glEnd();
    }
};
