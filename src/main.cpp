#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate(); //освобождает все ресурсы
    return 0;
}
