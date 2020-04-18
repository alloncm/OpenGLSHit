#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void ProcessIntput(GLFWwindow *window)
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

static void VerrifyShaderProgramLinking(unsigned int programId, const char* programName)
{
    int sucess;
    glGetProgramiv(programId, GL_LINK_STATUS, &sucess);
    if (!sucess)
    {
        char logInfo[512];
        glGetProgramInfoLog(programId, 512, NULL, logInfo);
        std::cout << "ERROR linking shaders program"<<programName<<"\n"
                  << logInfo << std::endl;
        exit(1);
    }
}

static void VerifyShaderCompilation(unsigned int shaderId, const char* shaderName)
{
    int sucess;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        char logInfo[512];
        glGetShaderInfoLog(shaderId, 512, NULL, logInfo);
        std::cout << "ERROR compiling"<< shaderName <<"shader\n"
                  << logInfo << std::endl;
        exit(1);
    }
}

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                   "}\0";
const char *anotherFragmentShaderSource = "#version 330 core\n"
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

    VerifyShaderCompilation(vertexShaderId, "Vertex");

    //fragment shader
    unsigned int regularFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(regularFragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(regularFragmentShaderId);

    VerifyShaderCompilation(regularFragmentShaderId, "regular Fragment");

    //yellow fragment shader
    unsigned int yellowFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowFragmentShaderId, 1, &anotherFragmentShaderSource, nullptr);
    glCompileShader(yellowFragmentShaderId);

    VerifyShaderCompilation(yellowFragmentShaderId, "yellow fragment");

    //linking
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderId);
    glAttachShader(shaderProgram, regularFragmentShaderId);
    glLinkProgram(shaderProgram);

    VerrifyShaderProgramLinking(shaderProgram, "regular");

    unsigned int yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShaderId);
    glAttachShader(yellowShaderProgram, yellowFragmentShaderId);
    glLinkProgram(yellowShaderProgram);

    VerrifyShaderProgramLinking(yellowShaderProgram, "yellow");

    glDeleteShader(vertexShaderId);
    glDeleteShader(regularFragmentShaderId);

    //data to draw
    float rectVertices[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    float firstTrigVerticies[]={
        -0.5f, 0.5f, 0.0f,
        -0.75f, -0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f
    };
    float secondTrigVerticies[] = {
        0.5f, 0.5f, 0.0f,
        0.75f, -0.5f, 0.0f,
        0.25f, -0.5f, 0.0f
    };
    unsigned int rectIndicies[] = {
        0, 1, 2,
        0, 2, 3};

    //GL objects
    //VAO
    unsigned int vertexArrayObj;
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);
    //EBO
    unsigned int elementBufferObj;
    glGenBuffers(1, &elementBufferObj);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObj);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndicies), rectIndicies, GL_STATIC_DRAW);
    //VBO
    unsigned int vertexBufferObj;
    glGenBuffers(1, &vertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTrigVerticies), firstTrigVerticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    unsigned int anotherVertexArrayObj;
    glGenVertexArrays(1, &anotherVertexArrayObj);
    glBindVertexArray(anotherVertexArrayObj);

    unsigned int anotherVertexBufferObj;
    glGenBuffers(1, &anotherVertexBufferObj);
    glBindBuffer(GL_ARRAY_BUFFER,anotherVertexBufferObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTrigVerticies),secondTrigVerticies, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    std::cout<<"Left SHIFT to view fill \nENTER to view lines"<<std::endl;
    
    while (!glfwWindowShouldClose(window))
    {
        ProcessIntput(window);

        //rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArrayObj);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(anotherVertexArrayObj);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}