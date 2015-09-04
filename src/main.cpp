// Link statically with GLEW
#define GLEW_STATIC

// Headers
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <SOIL.h>

#include "shader.hpp"
#include "texture.hpp"
#include "Textures.h"
#include "billboard.h"

GLFWwindow* window;

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(800, 600, "OpenGL", 0, 0); // Windowed
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // Create and compile our GLSL program from the shaders
    GLuint shaderProgram = LoadShaders( "shaders/texture.vert", "shaders/texture.frag" );

    glUseProgram(shaderProgram);

    Textures textures;
    textures.loadTextures("./images");

    Billboard dog(
        glm::vec3(-1.0f, 1.0f, 0.5f), 
        glm::vec3(-1.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 1.0f, 0.5f), 
                    shaderProgram,
        textures.getTexture("dog.jpg"));

    Billboard cat(
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, -1.0f, 0.0f), 
        glm::vec3(1.0f, -1.0f, 0.0f), 
        glm::vec3(1.0f, 0.0f, 0.0f), 
        shaderProgram,
        textures.getTexture("cat.png"));

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
           glfwSetWindowShouldClose(window, GL_TRUE);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle from the 2 triangles using 6 indices
        dog.draw();
        cat.draw();
    }

    glDeleteProgram(shaderProgram);
}
