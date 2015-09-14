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
#include "sphere.h"
#include "container.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;



GLFWwindow* window;

int main2()
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

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
                                glm::vec3(0,0,2), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                           );
    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model      = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around


    glUseProgram(shaderProgram);

    Textures textures;
    textures.loadTextures("./images");

    Container container;

        // std::shared_ptr<Node> cezanne(new Billboard(
        // glm::vec3(-10.0f, 10.0f, -20.0f), 
        // glm::vec3(-10.0f, -10.0f, -20.0f), 
        // glm::vec3(10.0f, -10.0f, -20.0f), 
        // glm::vec3(10.0f, 10.0f, -20.0f), 
        // shaderProgram,
        // textures.getTexture("cezanne-still-life-lrg.jpg")));
        //  container.add(cezanne);


        // std::shared_ptr<Node> dog(new Billboard(
        // glm::vec3(-1.0f, 1.0f, -1.0f),
        // glm::vec3(-1.0f, 0.0f, -1.0f), 
        // glm::vec3(0.0f, 0.0f, -1.0f), 
        // glm::vec3(0.0f, 1.0f, -1.0f), 
        //             shaderProgram,
        // textures.getTexture("dog.jpg")));
        //  container.add(dog);

        // std::shared_ptr<Node> cat(new Billboard(
        // glm::vec3(0.0f, 0.0f, -1.0f), 
        // glm::vec3(0.0f, -1.0f, -1.0f), 
        // glm::vec3(1.0f, -1.0f, -1.0f), 
        // glm::vec3(1.0f, 0.0f, -1.0f), 
        // shaderProgram,
        // textures.getTexture("cat.png")));
        //  container.add(cat);


        // std::shared_ptr<Node> ball(new Sphere(1.0f,
        // glm::vec3(0.0f, 0.0f, -1.0f), 
        // 2, 2,
        // shaderProgram,
        // textures.getTexture("dog.jpg")));
        //  container.add(ball);





    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
           glfwSetWindowShouldClose(window, GL_TRUE);
        }

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle from the 2 triangles using 6 indices
        container.draw();

    }

    glDeleteProgram(shaderProgram);
}
