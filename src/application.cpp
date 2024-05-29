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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 150.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float deltatime = 0.0f,lasttime = 0.0f;

float pitch = 0.0f;
float yaw = 0.0f;
bool firstMouse = true;

float lastX = 400, lastY = 300;
void static mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

};
void static key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    GLfloat cameraSpeed = 0.05f * deltatime * 1000.0f;
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

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
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
        va.layout_push<float>(3);
        va.addLayout();

        my_engine::Shader shader("res/shader/basic.shader");
        my_engine::Texture texture0("res/texture/1.png");
        my_engine::Texture texture1("res/texture/10.jpg");
        CheckGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        CheckGL(glEnable(GL_BLEND));

        shader.unbind();
        my_engine::Shader lightShader("res/shader/lighting.shader");
        lightShader.unbind();

        shader.bind();
        shader.SetUniform1i("mytexture1", 0);
        shader.SetUniform1i("mytexture2", 1);
        texture0.bind();
        texture1.bind(1);
        
        
        my_engine::model_trans trans("u_model",&shader);
        my_engine::projection pro("u_pro", &shader);
        my_engine::camera view("u_view", &shader);
        
        my_engine::model_trans trans2("u_model", &lightShader);
        

        while (!glfwWindowShouldClose(window))
        {
            glfwSwapBuffers(window);
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.bind();

            float now = glfwGetTime();
            float time = (cos(glfwGetTime()) + 1.0) / 2;
            shader.SetUniform1f("T_color", time);

            

            glm::vec3 lightpos = { 0.5f,1.0f,-0.3f };
            
            
            {
                trans.SetTranslate(glm::vec3(0.0f,-0.3f,0.6f));
                trans.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
                trans.SetRotate(now * 10.0f, glm::vec3(0.0f, 1.0f, 1.0f));
                CheckGL(glDrawArrays(GL_TRIANGLES, 0, 36));

                glm::vec3 lightcol(1.0f);
                glm::vec3 CameraPos(0.0f);
                shader.SetUniform3f("LightCol", lightcol);
                shader.SetUniform3f("LightPos", lightpos);
                shader.SetUniform3f("ViewPos", CameraPos);
                shader.unbind();
            }
            {
                lightShader.bind();
                trans2.SetTranslate(lightpos);
                trans2.SetRotate(90.0, glm::vec3(0.0, 1.0, 1.0));
                trans2.SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
                CheckGL(glDrawArrays(GL_TRIANGLES, 0, 36));
                lightShader.unbind();
            }
            
            double nowtime = glfwGetTime();
            deltatime = nowtime - lasttime; 
            lasttime = nowtime;
            //glfwSetKeyCallback(window, key_callback);
            //glfwSetCursorPosCallback(window, mouse_callback);
            


            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
