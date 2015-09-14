#pragma once

#include "node.h"

class Plane : public Node{

private:

public:
	Plane(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, 
		const glm::vec2& tx1, const glm::vec2& tx2, const glm::vec2& tx3, const glm::vec2& tx4,
		GLuint textureIn, GLuint shaderIn)  : Node(glm::vec3(), textureIn, shaderIn) {

		texture = textureIn;

	    GLfloat floorVertices[] = {
	        // Positions          // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
	        v1.x, v1.y,  v1.z,  tx1.s, tx1.t,
	        v2.x, v2.y,  v2.z,  tx2.s, tx2.t,
	        v3.x, v3.y,  v3.z,  tx3.s, tx3.t,

	        v1.x, v1.y,  v1.z,  tx1.s, tx1.t,
	        v3.x, v3.y,  v3.z,  tx3.s, tx3.t,
	        v4.x, v4.y,  v4.z,  tx4.s, tx4.t
	    };

	    glGenVertexArrays(1, &vao);
	    glGenBuffers(1, &vbo);
	    glBindVertexArray(vao);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), &floorVertices, GL_STATIC_DRAW);
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	    glBindVertexArray(0);

	}


	void draw() {
		Node::draw();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);  
	}

};