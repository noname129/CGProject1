#include "stdafx.h"
#include "GApp.h"
#include "GScene.h"
#include "GDrawable.h"
#include "GMonoPoly.h"
#include "GCanvas.h"

#include "Explosion.h"

namespace Glory {

GApp::GApp() {
	lastFrameTime = static_cast<float>(glfwGetTime());
	lastScene = nullptr;
}

GApp* GApp::Instance() {
	static GApp instance = GApp();
	return &instance;
}

void GApp::InitWindow(int width, int height, std::string title) {
	// glfw: initialize and configure
	if (!glfwInit()) {
		printf("GLFW initialisation failed!");
		glfwTerminate();
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// glfw window creation
	window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	SetFrameBufferSizeCallback(DefaultFramebufferSizeCallback);
	//glfwSetKeyCallback(window, key_callback);

	// OpenGL states
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Allow modern extension features
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialisation failed!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	windowWidth = width;
	windowHeight = height;
	windowTitle = title;

	// Default shader initialization
	GDrawable::defaultShader.initShader("Resources/shaders/global.vs", "Resources/shaders/global.fs");
	GMonoPoly::monotoneShader.initShader("Resources/shaders/monotone.vs", "Resources/shaders/monotone.fs");
	GCanvas::defaultShader.initShader("Resources/shaders/ui.vs", "Resources/shaders/ui.fs");

	inited = true;
}


void GApp::MainLoop() {
	if (!inited) {
		return;
	}

	while (!glfwWindowShouldClose(window)) {
		float currentFrameTime = static_cast<float>(glfwGetTime());
		if (currentScene) {
			currentScene->Update(currentFrameTime - lastFrameTime);
		}
		lastFrameTime = currentFrameTime;

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (currentScene) {
			currentScene->Render();
		}

		if (lastScene) {
			delete lastScene;
			lastScene = nullptr;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void GApp::SetScene(GScene* scene) {
	lastScene = currentScene;
	currentScene = scene;
}

void GApp::DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	GApp::Instance()->windowWidth = width;
	GApp::Instance()->windowHeight = height;
}

void GApp::SetFrameBufferSizeCallback(GLFWframebuffersizefun callback) {
	if (callback) {
		glfwSetFramebufferSizeCallback(window, callback);
	}
}

}