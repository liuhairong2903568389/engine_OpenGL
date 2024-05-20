#define GLEW_STATIC
#include<GLEW/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

#include"MyLog.h"
#include"Renderer.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"Camera.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    GLfloat cameraSpeed = 0.15f;
    if (key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if (key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if (key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    };
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    {
        float indices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        unsigned int index[] = {
            0,1,2,
            2,3,0,
            4,5,6,
            6,7,4,
            0,1,5,
            5,4,0,
            2,3,6,
            6,7,3,
            0,3,7,
            7,4,0,
            1,5,6,
            1,2,6
        };

        my_engine::VertexArray va;
        my_engine::VertexBuffer vb(indices, sizeof(indices));
        my_engine::IndexBuffer ib(index, sizeof(index));
        va.layout_push<float>(3);
        va.layout_push<float>(2);
        va.addLayout();

        my_engine::Shader shader("res/shader/basic.shader");
        my_engine::Texture texture0("res/texture/1.png");
        my_engine::Texture texture1("res/texture/10.jpg");
        CheckGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        CheckGL(glEnable(GL_BLEND));

        shader.SetUniform1i("mytexture1", 0);
        shader.SetUniform1i("mytexture2", 1);
        texture0.bind();
        texture1.bind(1);
        
        
        //my_engine::translational trans("u_MVP",&shader);
        //glm::vec3 scales(2.0f, 2.0f, 2.0f), rotates(0.0f, 0.0f, 1.0f), translations(0.0f, 0.0f, 1.0f);
        //glm::mat4 u_MVP = glm::translate(glm::mat4(1.0f), translations);
        //u_MVP = glm::rotate(u_MVP, glm::radians(90.0f), rotates);
        //u_MVP = glm::scale(u_MVP, scales);

        //glm::mat4 view = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

       // glm::mat4 view = glm::ortho( -3.0f, 3.0f, -3.0f, 3.0f, -2.0f, 2.0f);
        //u_MVP = view * u_MVP;
        //trans.Set_basictransform(scales, 180.0f, rotates, translations);
        glm::mat4 u_MVP(1.0f);
        
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 500.0f);

        glm::mat4 view;
        view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));


        while (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            
            
            glm::mat4 views = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            

            float time = (cos(glfwGetTime()) + 1.0) / 2;
            shader.SetUniform1f("T_color", time);
            

            /*float t_angle = glfwGetTime();
            trans.SetTranslate(glm::vec3(1.0), t_angle, glm::vec3(0.0,0.0,1.0), glm::vec3(0.0));*/

            glClearColor(0.2f, 0.5f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glm::vec3 cubePositions[] = {
                  glm::vec3(0.0f,  0.0f,  0.0f),
                  glm::vec3(2.0f,  5.0f, -15.0f),
                  glm::vec3(-1.5f, -2.2f, -2.5f),
                  glm::vec3(-3.8f, -2.0f, -12.3f),
                  glm::vec3(2.4f, -0.4f, -3.5f),
                  glm::vec3(-1.7f,  3.0f, -7.5f),
                  glm::vec3(1.3f, -2.0f, -2.5f),
                  glm::vec3(1.5f,  2.0f, -2.5f),
                  glm::vec3(1.5f,  0.2f, -1.5f),
                  glm::vec3(-1.3f,  1.0f, -1.5f)
            };
            for (int i = 0; i < 10; i++) {
                
                glm::mat4 view = glm::translate(glm::mat4(1.0f), cubePositions[i]+glm::vec3(0.00,0.0,-3.0));
                glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * 1.0f, glm::vec3(1.0f, 0.3f + 0.4f*i, 0.05f * i));
                u_MVP = projection *views * view   * model;
                shader.SetUniformmat4("u_MVP", u_MVP);
                CheckGL(glDrawArrays(GL_TRIANGLES, 0, 36));
            }
            
            

            glfwSetKeyCallback(window, key_callback);



            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
