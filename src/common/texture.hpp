#pragma once

#include <string>
#include <SOIL.h>

void load2DTexture(GLuint textureID, const std::string& fileName);


// This function loads a texture from file. Note: texture loading functions like these are usually 
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio). 
// For learning purposes we'll just define it as a utility function.
GLuint loadTexture(const GLchar* path, GLboolean alpha);

// Generates a texture that is suited for attachments to a framebuffer
GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil, GLuint screenWidth, GLuint screenHeight);