#include "TexturedModelShape3D.hpp"
#include <GL/glew.h>
#include <iostream>


TexturedModelShape3D::TexturedModelShape3D(
    const std::vector<float>& verts,
    const std::vector<float>& colors,
    glm::vec3 modulateColor,
    const std::vector<float>& normals,
    const std::vector<unsigned int>& indices,
    const std::vector<float>& texCoord,
    GLuint textureIdInput 
) : ModelShape3D(verts, colors, modulateColor, normals, indices, texCoord)
{

    setTexture(textureIdInput);


}


void TexturedModelShape3D::draw(const glm::mat4& view) {
    bool textureWasBound = false;
    if (textureId > 0) {

        glEnable(GL_TEXTURE_2D); 
        glBindTexture(GL_TEXTURE_2D, textureId);
        textureWasBound = true;
    }
    else {
 
        glDisable(GL_TEXTURE_2D); 
    }

    ModelShape3D::draw(view);


    if (textureWasBound) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


void TexturedModelShape3D::setTexture(GLuint texture) {

    ModelShape3D::setTexture(texture);

}
