#ifndef SHADER_HPP
#define SHADER_HPP

// Include GLM
#include "../external/glm-0.9.4.0/glm/glm.hpp"
#include "../external/glm-0.9.4.0/glm/gtc/matrix_transform.hpp"
#include <QOpenGLFunctions_4_5_Core>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
