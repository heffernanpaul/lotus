// Std. Includes
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "shader.h"
#include "camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

#include "texture.hpp"
#include "cube.h"
#include "sphere.h"
#include "plane.h"
#include "container.h"


void Do_Movement();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


class OpenGlApp {

private:
    GLuint screenWidth, screenHeight;

    Camera camera;
    bool keys[1024];
    GLfloat lastX = 400, lastY = 300;
    bool firstMouse = true;

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

public:

    // Moves/alters the camera positions based on user input
    void doMovement()
    {
        // Camera controls
        if(keys[GLFW_KEY_W])
            camera.ProcessKeyboard(FORWARD, deltaTime*3);
        if(keys[GLFW_KEY_S])
            camera.ProcessKeyboard(BACKWARD, deltaTime*3);
        if(keys[GLFW_KEY_A])
            camera.ProcessKeyboard(LEFT, deltaTime);
        if(keys[GLFW_KEY_D])
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // Is called whenever a key is pressed/released via GLFW
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;  
    }

    void mouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos; 
        
        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }   

    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(yoffset);
    }



    OpenGlApp(GLuint screenWidthIn, GLuint screenHeightIn) 
        : screenWidth(screenWidthIn), screenHeight(screenHeightIn), camera(glm::vec3(0.0f, 0.0f, 3.0f)){

    }


    // The MAIN function, from here we start our application and run our Game loop
    int run()
    {
        // Init GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
        glfwMakeContextCurrent(window);

        // Set the required callback functions
        glfwSetKeyCallback(window, key_callback);

        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // Options
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	

        // Initialize GLEW to setup the OpenGL Function pointers
        glewExperimental = GL_TRUE;
        glewInit();

        // Define the viewport dimensions
        glViewport(0, 0, screenWidth, screenHeight);

        // Setup some OpenGL options
        glDepthFunc(GL_LESS);
        
        // Setup and compile our shaders
        Shader shader("shaders/framebuffers.vs", "shaders/framebuffers.frag");

        // Load textures
        GLuint cubeTexture = loadTexture("resources/textures/elise.jpg", false);
        GLuint floorTexture = loadTexture("resources/textures/grass.jpg", false);
        GLuint skyTexture = loadTexture("resources/textures/cezanne-still-life-lrg.jpg", false);

        Container container;
       //  for (int i = 0; i < 5; i++) {

       //      for (int j = 0; j < 5; j++) {

       //          for (int k = 0; k < 5; k++) {

       //              std::shared_ptr<Node> cube(new Cube(glm::vec3(-20.0f + (6.0f*i), -20.0f + (6.0f*k), -20.0f + (6.0f*j)), 0.5f, cubeTexture));    
       //              container.add(cube);
       //          }
       //      }
       // }
        for (int i = 0; i < 5; i++) {

            for (int j = 0; j < 5; j++) {

                for (int k = 0; k < 5; k++) {
                    std::shared_ptr<Node> sphere(new Sphere(1.5f, glm::vec3(-20.0f + (6.0f*i), -20.0f + (6.0f*k), -20.0f + (6.0f*j)), 32, 32, cubeTexture, shader.Program));    
                    container.add(sphere);
                }
            }
        }

        GLfloat width = 50.0f;
        GLfloat height = -20.0f;
        std::shared_ptr<Node> lawn(new Plane(
            glm::vec3(width, height, width),
            glm::vec3(-width, height, width),
            glm::vec3(-width, height, -width),
            glm::vec3(width, height, -width),
            glm::vec2(5.0f, 0.0f),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(0.0f, 5.0f),
            glm::vec2(5.0f, 5.0f),
            floorTexture, shader.Program
            ));
        container.add(lawn);

        GLfloat skyWidth = 45.0f;
        GLfloat skyHeight = 25.0f;
        GLfloat dist = -20.0f;
        std::shared_ptr<Node> sky(new Plane(
            glm::vec3(-skyWidth, skyHeight, dist),
            glm::vec3(skyWidth, skyHeight, dist),
            glm::vec3(skyWidth, -skyHeight, dist),
            glm::vec3(-skyWidth, -skyHeight, dist),
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            skyTexture, shader.Program
            ));
        container.add(sky);

        while(!glfwWindowShouldClose(window))
        {
            // Set frame time
            GLfloat currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            // Check and call events
            glfwPollEvents();
            doMovement();
            
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer so why bother with clearing?

            glEnable(GL_DEPTH_TEST);
            // Set uniforms
            shader.Use();
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

            glBindTexture(GL_TEXTURE_2D, skyTexture);

            container.draw();

            glfwSwapBuffers(window);
        }

        glfwTerminate();
        return 0;
    }
};

OpenGlApp* app;

int main(int argc, char** argv) {
    OpenGlApp myApp(1000,700);
    app = &myApp;
    app->run();

}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    app->keyCallback(window, key, scancode, action,  mode);  
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    app->mouseCallback(window, xpos, ypos);
}   

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    app->scrollCallback(window, xoffset, yoffset);
}
