#pragma once

#include <GL/glew.h>

namespace util {
	GLuint loadShaders(const char* vertex_file_path, const char* fragment_file_path);
}