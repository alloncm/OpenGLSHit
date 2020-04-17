#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void ProcessIntput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("failed to crate a window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to initialize glad");
        glfwTerminate();
        return 1;
    }
    glViewport(0, 0, 800, 600);

    //vertex shader
    unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);

    int sucess;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        char logInfo[512];
        glGetShaderInfoLog(vertexShaderId, 512, NULL, logInfo);
        std::cout << "ERROR compiling vertex shader\n"
                  << logInfo << std::endl;
        return 1;
    }

    //fragment shader
    unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        char logInfo[512];
        glGetShaderInfoLog(vertexShaderId, 512, NULL, logInfo);
        std::cout << "ERROR compiling fragment shader\n"
                  << logInfo << std::endl;
        return 1;
    }

    //linking
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, fragmentShaderId);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess)
    {
        char logInfo[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, logInfo);
        std::cout << "ERROR linking shaders program shader\n"
                  << logInfo << std::endl;
        return 1;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    float vertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f};
    unsigned int indicies[] = {
        0, 1, 2,
        0, 2, 3};
    unsigned int vertexArrayObj;
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);

    unsigned int elementBufferObj;
    glGenBuffers(1, &elementBufferObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    unsigned int vertexBufferObj;
    glGenBuffers(1, &vertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        ProcessIntput(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}