#include "Textures.h"
#include "texture.hpp"
#include <dirent.h>
#include <vector>
#include <iostream>

void Textures::loadTextures(const std::string& folder) {

    GLuint tex[2];
    glGenTextures(2, tex);


	DIR *dpdf;
	struct dirent *epdf;

	dpdf = opendir(folder.c_str());
	if (dpdf != NULL){
	   while ((epdf = readdir(dpdf))){
	   		if (epdf->d_name[0] != '.') {
		      	std::string name(epdf->d_name);
		      	std::cout << "Filename: " << name << std::endl;
		      	filenames.push_back(name);
		      }
	   }
	}
  	std::cout << "Generating Textures" << std::endl;
    idList = new GLuint[filenames.size()];
    glGenTextures(filenames.size(), idList);


	for (int i = 0; i < filenames.size(); i++) {
  	std::cout << "Loading Texture " << filenames[i] << " into " << idList[i] << std::endl;
	    load2DTexture(idList[i], folder + "/" + filenames[i]);
	}
}

GLuint Textures::getTexture(const std::string& name) {

	for (int i = 0; i < filenames.size(); i++) {
		if (filenames[i] == name) {
			std::cout << "Found texture : " << idList[i] << std::endl;
			return idList[i];
		}
	}
	return 0;
}