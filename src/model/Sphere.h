#pragma once

#include "node.h"
#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <iostream>


class Sphere : public Node {

private:
	GLfloat radius;
	GLuint texture;
    GLuint ebo;
    GLuint vbo;
    GLuint vao;
    int numVertices;

public:
	Sphere(GLfloat radius, glm::vec3 positionIn, int nSlices, int nStacks, GLuint texture, const GLuint shaderProgram) ;

	~Sphere() {
		std::cout << "Deleting Sphere" << std::endl;
	    glDeleteBuffers(1, &ebo);
    	glDeleteBuffers(1, &vbo);
	    glDeleteVertexArrays(1, &vao);

	}

	void draw();

};