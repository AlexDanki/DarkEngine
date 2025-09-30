#include <glad/glad.h>
#include "Engine.h"
#include <iostream> 
#include "TimeManager.h"
#include "DefaultScene.h"
#include "../physics/PhysicalWorld.h"
#include "Window.h"
#include <SDL.h>

void frameBufferResizeCallback(GLFWwindow* window, int width, int height);

bool start = false;
double tempo = 0;
TimeManager timeManager(60);
const float FPS = 5;

//Data::LoadData loader;

Engine::Engine():
	m_window(nullptr), 
    isRunning(false), 
    m_deltaTime(0.0), 
    sceneManager(nullptr), 
    defaultScene(nullptr),
	renderer(nullptr),
    allLoaded(false),
    m_monitor(nullptr),
    loader(nullptr)
{
	sceneManager = new SceneManager(defaultScene);
    defaultScene = new DefaultScene(this);
    renderer = new Renderer();
    loader = new Data::LoadData();
}

Engine::~Engine()
{
}

void Engine::init()
{
    loader->Load();
    if (loader->AllDataLoaded())
    {

        /* Initialize the library */
        if (!glfwInit())
            std::cerr << "Failed to initialize GLFW" << std::endl;;

        m_monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

        WindowInfo ws;
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(mode->width, mode->height, ws.WindowName.c_str(), nullptr, nullptr);

        if (!m_window)
        {
            glfwTerminate();
            std::cerr << "Failed to initialize window's" << std::endl;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
        glfwSwapInterval(1);

        renderer->init();
        renderer->setClearScreen(0.6f, 0.8f, 0.9f, 1.0f);
        sceneManager->changeScene(defaultScene);
        //start();

        m_ticksCount = SDL_GetTicks();
        isRunning = true;
    }
    else
    {
        std::cerr << "Erro ao carregar modelos 3D\n";
    }
}

void Engine::run()
{

    while (isRunning && !glfwWindowShouldClose(m_window))
    {
        processInput();
        update();
        render();
    }
}

void Engine::shutdown()
{
	glfwDestroyWindow(m_window);
    glfwTerminate();
    delete sceneManager;
    
	for (Scene* scene : scenes) {
		delete scene;
		std::cout << "Scene deleted. Remaining scenes: " << scenes.size() - 1 << std::endl;
	}

}

void Engine::addScenes(Scene* scene)
{
	scenes.push_back(scene);
    std::cout << "Scene added. Total scenes: " << scenes.size() << std::endl;
}

void Engine::start()
{
    //sceneManager->getCurrentScene()->init();
}

void Engine::processInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
		
    glfwPollEvents();
}

void Engine::update()
{
    
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + ( FPS / 1000 )));

    m_deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

    if (m_deltaTime > 0.05f)
        m_deltaTime = 0.05f;

    m_ticksCount = SDL_GetTicks();
	sceneManager->updateCurrentScene(m_deltaTime);
}

void Engine::render()
{
    /* Render here */

    renderer->beginFrame();

    sceneManager->renderCurrentScene(renderer);
    draw();
    
    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);
}

void Engine::draw()
{
}

void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}