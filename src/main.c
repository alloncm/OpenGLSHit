#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void ProcessIntput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL, NULL);
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
    glViewport(0,0,800,600);

    while (!glfwWindowShouldClose(window))
    {
        ProcessIntput(window);

        //rendering
        glClearColor(0.2,0.3,0.3,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}