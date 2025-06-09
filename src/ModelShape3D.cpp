#include "ModelShape3D.hpp"
#include <GL/glew.h> 
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


ModelShape3D::ModelShape3D(
    const std::vector<float>& verts,
    const std::vector<float>& colors,
    glm::vec3 modulateColor,
    const std::vector<float>& normals,
    const std::vector<unsigned int>& indices,
    const std::vector<float>& texCoord
) : verts(verts),
colors(colors),
modulateColor(modulateColor),
normals(normals),
indices(indices),
texCoords(texCoord),
textureId(0)
{

}


void ModelShape3D::draw(const glm::mat4& view) {

    glm::mat4 modelView = view * getTransform();


    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(modelView));


    glColor3fv(glm::value_ptr(modulateColor));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, verts.data());


    if (!colors.empty()) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, colors.data());
    }
    else {
        glDisableClientState(GL_COLOR_ARRAY);
    }


    if (!normals.empty()) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, normals.data());
    }
    else {
        glDisableClientState(GL_NORMAL_ARRAY);
    }


    if (!texCoords.empty() && textureId > 0) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, texCoords.data());
    }
    else {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }


    if (!indices.empty()) {
        glDrawElements(
            GL_TRIANGLES,
            indices.size(),
            GL_UNSIGNED_INT,
            indices.data());
    }
    else {
        std::cerr << "Brak indeksow do rysowania." << std::endl;
    }


    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);


}


void ModelShape3D::setTexture(GLuint texture) {
    this->textureId = texture;
}
