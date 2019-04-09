#include "stdafx.h"
#include "GScene.h"

namespace Glory {

class GApp {
private:
	GLFWwindow *window;
	GScene *currentScene;
	bool inited;

	int windowWidth, windowHeight;

public:
	std::string windowTitle;

	static GApp& Instance();

	void InitWindow(int width, int height, std::string title = "");
	void MainLoop();

	void SetScene(GScene* scene);

	int GetWindowWidth() { return windowWidth; }
	int GetWindowHeight() { return windowHeight; }

	void SetFrameBufferSizeCallback(GLFWframebuffersizefun callback);

	static void DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);
};

}