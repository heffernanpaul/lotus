#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>

class Textures {

private:
	std::vector<std::string> filenames;
	GLuint *idList;

public:
	void loadTextures(const std::string& folder);
	GLuint getTexture(const std::string& name); 

	~Textures() {
		if (idList != NULL) {
			std::cout << "Deleting textures" << std::endl;
			glDeleteTextures(filenames.size(), idList);
		}
	}
};
