#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Node {

protected:
	glm::mat4 position;
    GLuint vao, vbo, texture, shader;

	Node() : position(glm::mat4()), vao(0), vbo(0) , texture(0) {}
	Node(GLuint textureIn) : vao(0), vbo(0) , texture(textureIn) {}
	Node(const glm::vec3& positionIn, GLuint textureIn, GLuint shaderIn) : vao(0), vbo(0) , texture(textureIn), shader(shaderIn)  {
		position = glm::translate(glm::mat4(1.0f), positionIn);
	}
public:
	virtual void draw() {
        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(position));
        glBindTexture(GL_TEXTURE_2D, texture);
	}

	virtual ~Node() {
		
	}

};

typedef std::shared_ptr<Node> NodePtr;
