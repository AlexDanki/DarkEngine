#include <glad/glad.h>
#include "Engine.h"
#include <iostream> 
#include "TimeManager.h"
#include "../Game/SceneLevelFPS.h"
#include "DefaultScene.h"
#include "../physics/PhysicalWorld.h"
#include "Window.h"

void frameBufferResizeCallback(GLFWwindow* window, int width, int height);

bool start = false;
double tempo = 0;

Engine::Engine():
	m_window(nullptr), 
    isRunning(false), 
    m_deltaTime(0.0), 
    sceneManager(nullptr), 
    defaultScene(nullptr),
	renderer(nullptr)
{
	sceneManager = new SceneManager(defaultScene);
    defaultScene = new DefaultScene(this);
    renderer = new Renderer();
}

Engine::~Engine()
{
}

void Engine::init()
{
    /* Initialize the library */
    if (!glfwInit())
        std::cerr << "Failed to initialize GLFW" << std::endl;;

    WindowInfo ws;
    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(ws.Width, ws.Height, ws.WindowName.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        std::cerr << "Failed to initialize window" << std::endl;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
    glfwSwapInterval(1);
    
	renderer->init();
    renderer->setClearScreen(0.6f, 0.8f, 0.9f, 1.0f);
    sceneManager->changeScene(defaultScene);
    //start();

    isRunning = true;
}

void Engine::run()
{
	TimeManager timer(60.0);
    /* Loop until the user closes the window */
    while (isRunning && !glfwWindowShouldClose(m_window))
    {
		timer.startTime();

		processInput();
		update();
		render();

		timer.endTime();
		timer.sleepIfNeeded();
		m_deltaTime = timer.getDeltaTime();
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