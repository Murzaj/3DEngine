#include "BitmapHandler.hpp"
#include <GL/glew.h> 
#define STB_IMAGE_IMPLEMENTATION 
#include "ext/stb_image.h"
#include <iostream>


GLuint BitmapHandler::loadBitmap(const std::string& name, const std::string& filename, GLint magFilter, GLint minFilter) {
    if (loadedTextures.count(name)) {
        return loadedTextures[name];
    }

    GLuint textureID;
    glGenTextures(1, &textureID); 

    int width, height, nrComponents;

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else {
            std::cerr << "Nieobslugiwana liczba komponentow (" << nrComponents << ") in " << filename << std::endl;
            stbi_image_free(data);
            glDeleteTextures(1, &textureID);
            return 0; 
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (minFilter == GL_LINEAR || minFilter == GL_NEAREST) ? GL_LINEAR_MIPMAP_LINEAR : minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter); 

        stbi_image_free(data); 
        std::cout << "Zaladowano teksture '" << name << "' (" << filename << ") ID: " << textureID << std::endl;

        loadedTextures[name] = textureID; 
        return textureID;
    }
    else {
        std::cerr << "Nie udalo sie zaladowac tekstury ze sciezki: " << filename << std::endl;
        stbi_image_free(data);
        glDeleteTextures(1, &textureID);
        return 0; 
    }
}


GLuint BitmapHandler::getBitmap(const std::string& name) {
    auto it = loadedTextures.find(name);
    if (it != loadedTextures.end()) {
        return it->second; 
    }
    else {
      
        return 0; 
    }
}


void BitmapHandler::removeBitmap(const std::string& name) {
    auto it = loadedTextures.find(name);
    if (it != loadedTextures.end()) {
        std::cout << "Usuwanie tekstury '" << name << "' ID: " << it->second << std::endl;
        glDeleteTextures(1, &(it->second)); 
        loadedTextures.erase(it); 
    }
    else {
      
    }
}

BitmapHandler::~BitmapHandler() {
    std::cout << "Czyszczenie" << loadedTextures.size() << " tekstur...." << std::endl;
    for (auto const& [name, val] : loadedTextures) {
        std::cout << "  Usuwanie tekstury '" << name << "' ID: " << val << std::endl;
        glDeleteTextures(1, &val);
    }
    loadedTextures.clear();
    std::cout << "Czyszczenie zakonczone." << std::endl;
}
