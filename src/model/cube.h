#pragma once

#include <vector>
#include "node.h"

class Cube : public Node {

private:


public:
	Cube(glm::vec3 position,  GLfloat radius, GLuint textureIn, GLuint shaderIn) : Node(position, textureIn, shaderIn) {

	    GLfloat cubeVertices[] = {
	        // Positions          // Texture Coords
	        -radius, -radius, -radius,  0.0f, 0.0f,
	         radius, -radius, -radius,  1.0f, 0.0f,
	         radius,  radius, -radius,  1.0f, 1.0f,
	         radius,  radius, -radius,  1.0f, 1.0f,
	        -radius,  radius, -radius,  0.0f, 1.0f,
	        -radius, -radius, -radius,  0.0f, 0.0f,

	        -radius, -radius,  radius,  0.0f, 0.0f,
	         radius, -radius,  radius,  1.0f, 0.0f,
	         radius,  radius,  radius,  1.0f, 1.0f,
	         radius,  radius,  radius,  1.0f, 1.0f,
	        -radius,  radius,  radius,  0.0f, 1.0f,
	        -radius, -radius,  radius,  0.0f, 0.0f,

	        -radius,  radius,  radius,  1.0f, 0.0f,
	        -radius,  radius, -radius,  1.0f, 1.0f,
	        -radius, -radius, -radius,  0.0f, 1.0f,
	        -radius, -radius, -radius,  0.0f, 1.0f,
	        -radius, -radius,  radius,  0.0f, 0.0f,
	        -radius,  radius,  radius,  1.0f, 0.0f,

	         radius,  radius,  radius,  1.0f, 0.0f,
	         radius,  radius, -radius,  1.0f, 1.0f,
	         radius, -radius, -radius,  0.0f, 1.0f,
	         radius, -radius, -radius,  0.0f, 1.0f,
	         radius, -radius,  radius,  0.0f, 0.0f,
	         radius,  radius,  radius,  1.0f, 0.0f,

	        -radius, -radius, -radius,  0.0f, 1.0f,
	         radius, -radius, -radius,  1.0f, 1.0f,
	         radius, -radius,  radius,  1.0f, 0.0f,
	         radius, -radius,  radius,  1.0f, 0.0f,
	        -radius, -radius,  radius,  0.0f, 0.0f,
	        -radius, -radius, -radius,  0.0f, 1.0f,

	        -radius,  radius, -radius,  0.0f, 1.0f,
	         radius,  radius, -radius,  1.0f, 1.0f,
	         radius,  radius,  radius,  1.0f, 0.0f,
	         radius,  radius,  radius,  1.0f, 0.0f,
	        -radius,  radius,  radius,  0.0f, 0.0f,
	        -radius,  radius, -radius,  0.0f, 1.0f
	    };

	    glGenVertexArrays(1, &vao);
	    glGenBuffers(1, &vbo);
	    glBindVertexArray(vao);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	    glBindVertexArray(0);

	}

	void draw() {

		Node::draw();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);            
	}




};
