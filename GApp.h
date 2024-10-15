#include "stdafx.h"

#ifndef __GAPP_H__
#define __GAPP_H__

namespace Glory {

class GScene;

class GApp {

private:
	GLFWwindow * window;
	GScene *currentScene, *lastScene;
	bool inited;

	int windowWidth, windowHeight;

	float lastFrameTime;

public:
	GApp();

	GLFWwindow* Window() {
		return window;
	}
	std::string windowTitle;

	static GApp* Instance();

	void InitWindow(int width, int height, std::string title = "");
	void MainLoop();

	GScene* Scene() const { return currentScene; }
	void SetScene(GScene* scene);

	int GetWindowWidth() { return windowWidth; }
	int GetWindowHeight() { return windowHeight; }

	void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback);

	static void DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};

}

#endif