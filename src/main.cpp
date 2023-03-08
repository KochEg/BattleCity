#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"

GLfloat point[] = { 0.0f, 0.5f, 0.0f,
                    0.5f, -0.5f, 0.0f,
                   -0.5f, -0.5f, 0.0f };

GLfloat colors[] = { 1.0f,0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 1.0f };


int g_windowSizeX = 640; //переменные дл€ размера окна
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) //функци€ изменени€ размера окна пользователем
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);/*‘ункци€ показывает где мы хотим рисовать в какой области окна, параметры передаем координаты нижнего левого угла окна
    , дале передаем ширину и высоту окна */
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) //функци€ дл€ передачи нажайтий клавиш
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //если нажать esc программа закроетс€ 
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(int argc, char** argv)
{
    GLFWwindow* pWindow;
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit() failed!" << std::endl; //если функци€ не запустилась
        return -1;
    }
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //если верси€ GLWF меньше 4.6 то ,не сможет создать окно
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//функции которые нам не нужны (свз€анные с обратной совместимостью)

    /* Create a windowed mode window and its OpenGL context */
    pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle-City", nullptr, nullptr);
    if (!pWindow) //если окно не было создано выходим из программы
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);  //контекст дл€ текущего окна
    
    if(!gladLoadGL()) //инициализируем библеотеку glad
    {
     	std::cout << "Can't load GLAD!" << std::endl;
    }
    
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl; //кака€ видеокарта рендерит
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; //верси€ OpenGL

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0; /*создаем буффер из оперативной пам€ти в видеопам€ть*/
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0); /*включает нулевую позицию в шейдере*/
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1); /*включает нулевую позицию в шейдере*/
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);


            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate(); //освобождает все ресурсы
    return 0;
}
