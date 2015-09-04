#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <iostream>

class Billboard {

private:
	GLuint texture;
	GLfloat *vertices;
    GLuint ebo;
    GLuint vbo;
    GLuint vao;

public:
	Billboard(const glm::vec3& tl, const glm::vec3& bl, const glm::vec3& br, const glm::vec3& tr, const GLuint shaderProgram,
		const GLuint texture);

	~Billboard() {
		std::cout << "Deleting Billboard" << std::endl;
	    glDeleteBuffers(1, &ebo);
    	glDeleteBuffers(1, &vbo);
	    glDeleteVertexArrays(1, &vao);

	}
	void draw();
};